#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>

#include "Server.hxx"
#include "json.hpp"

#define BUFFER_SIZE 32000

extern std::string username;
extern U32 userID;
extern bool isReady;

int set_non_blocking(int);
std::vector<std::string> splitJson(const std::string&);

// contructor.
Server::Server(const std::string& addr, U16 port)
{
	_buffer = new char[BUFFER_SIZE];
	_port = port;
	_address = addr;
	_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (_socket < 0)
	{
		std::cerr << "Server socket creation error!\n";
		exit(-1);
	}

	// Set the socket to non-blocking
	int flags = fcntl(_socket, F_GETFL, 0);
	if (flags == -1) {
		std::cerr << "Error getting socket flags: " << strerror(errno) << std::endl;
		close(_socket);
		exit(-1);
	}
	if (fcntl(_socket, F_SETFL, flags | O_NONBLOCK) == -1) {
		std::cerr << "Error setting socket to non-blocking: " << strerror(errno) << std::endl;
		close(_socket);
		exit(-1);
	}

	int flag = 1;
	if (setsockopt(_socket, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag)) < 0) {
		std::cerr << "Error disabling Nagle's algorithm: " << \
				strerror(errno) << std::endl;
		close(_socket);
		exit(-1);
	}

	sockaddr_in server_addr;
	std::memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_pton(AF_INET, addr.c_str(), &server_addr.sin_addr);

	int connectResult = connect(_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (connectResult < 0 && errno != EINPROGRESS)
	{
		std::cerr << "Server connection error!\n";
		close(_socket);
		exit(-1);
	}

	struct pollfd fds;
	fds.fd = _socket;
	fds.events = POLLOUT;

	int pollResult = poll(&fds, 1, 5000);
	if (pollResult < 0) {
		std::cerr << "Poll error!\n";
		close(_socket);
		exit(-1);
	} else if (pollResult == 0) {
		std::cerr << "Connection timeout!\n";
		close(_socket);
		exit(-1);
	}

	// check if connection is successfull.
	int so_error;
	socklen_t len = sizeof(so_error);
	if (getsockopt(_socket, SOL_SOCKET, SO_ERROR, &so_error, &len) < 0) {
		std::cerr << "getsockopt error!\n";
		close(_socket);
		exit(-1);
	}
	if (so_error != 0) {
		std::cerr << "Connection failed: " << strerror(so_error) << "\n";
		close(_socket);
		exit(-1);
	}

	std::cout << "Connected successfully!\n";

	std::string message = "{\"Command\" : \"Identification\", \"Username\" : \"" \
			   + username + "\" }";
	std::cout << message << '\n';
	send_data(message);

	std::string response = "";
	bool repeat = true;
	while (repeat)
	{
		response = dequeue_response();
		if (response == "")
			continue;
		json responseJSON;
		try
		{
			responseJSON = json::parse(response);
			if (responseJSON["Command"] != "Acception")
				continue;
			if (responseJSON["Status"] != "Successful")
			{
				std::cerr << "Unsuccessful server connection! Server refused connection.\n";
				exit(-1);
			}
			userID = responseJSON["UserID"];
			std::cout << "Server accepted connection. UserID = " << userID << '\n';
			repeat = false;
		}
		catch(const json::parse_error& e)
		{
			std::cerr << "Server creation response exception ; Parse error at byte : " << e.byte << " : " << e.what() << " ; String : " << response << '\n';
		}
		catch (const json::type_error& e)
		{
			std::cerr << "Server creation response : exception ; Type error : " << e.what() << " ; String : " << response <<'\n';
		}
		catch (const json::out_of_range& e)
		{
			std::cerr << "Server creation response : exception ; Out of range error : " << e.what() << " ; String : " << response << '\n';
		}
	}
}

// Server's destructor.
Server::~Server()
{
	// just close socket.
	close(_socket);
	delete [] _buffer;
}

// make request of room creation to server and connect to this room.
I32 Server::create_room(const GameParameter& params)
{
	json j;
	j["Command"] = "CreateRoom";
	j["User"]["UserID"] = userID;
	j["Parameters"]["PlayersCount"] = params.playersCount;
	j["Parameters"]["StartLevel"] = params.startLevel;
	j["Parameters"]["QueueType"] = params.isSameQueue ? "Same" : "Different";
	send_data(j.dump());
	do
	{
		std::string response = dequeue_response();
		if (response == "")
			continue;
		json responseJSON;
		try
		{
			responseJSON = json::parse(response);
			std::string command = responseJSON["Command"];
			if (command != "RoomCreationResponse")
				continue;
			if (responseJSON["Status"] == "Successful")
				return responseJSON["RoomID"];
			else
				return 0;
		}
		catch(const json::parse_error& e)
                {
                        std::cerr << "Room creation response ; Parse error at byte : " << e.byte << " : " << e.what() << "; String : " << response << '\n';
                }
                catch (const json::type_error& e)
                {
                        std::cerr << "Room creation response ; Type error : " << e.what() << " ; String : " << response << '\n';
                }
                catch (const json::out_of_range& e)
                {
                        std::cerr << "Room creation response ; Out of range error : " << e.what() << " ; String : " << response << '\n';
                }
	} while(1);

	return 0;
}

// connect to an existing room.
bool Server::connect_to_room(I32 id)
{
	json j;
	j["Command"] = "ConnectToRoom";
	j["Parameters"]["RoomID"] = id;
	send_data(j.dump());
	do
	{
		std::string response = dequeue_response();
		if (response == "")
			continue;
		json responseJSON;
		try
		{
			responseJSON = json::parse(response);
			std::string command = responseJSON["Command"];
			if (command != "RoomConnectionResponse")
				continue;
			if (responseJSON["Status"] == "Successful")
				return true;
			else
				return false;
		}
		catch(const json::parse_error& e)
		{
			std::cerr << "Room connection response ; Parse error at byte : " << e.byte << " : " << e.what() << '\n';
		}
		catch (const json::type_error& e)
		{
			std::cerr << "Room connection response ; Type error : " << e.what() << '\n';
		}
		catch (const json::out_of_range& e)
		{
			std::cerr << "Room connection response ; Out of range error : " << e.what() << '\n';
		}
	} while(1);
	return false;
}

// get room's parameters.
void Server::get_room_parameters()
{
	json request;
	request["Command"] = "GetRoomParameters";
	send_data(request.dump());
}

// make me ready.
void Server::make_ready()
{
	json j;
	j["Command"] = "BeReady";
	j["IsReady"] = "Yes";
	send_data(j.dump());
	isReady = true;
}

// make me non-ready.
void Server::make_non_ready()
{
	json j;
	j["Command"] = "BeReady";
	j["IsReady"] = "No";
	send_data(j.dump());
	isReady = false;
}

// send data to server.
bool Server::send_data(const std::string& str)
{
	size_t totalSent = 0;
	while (totalSent < str.size())
	{
		int bytesSent = send(_socket, str.c_str() + totalSent, str.size() - totalSent + 1, 0);
		if (bytesSent < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				std::cout << "Send would block, try again later." << std::endl;
			}
			else {
				std::cerr << "Error sending data: " << strerror(errno) << std::endl;
			}
			return false;
		}
		totalSent += bytesSent;
	}
	return true;
}

// dequeue response.
std::string Server::dequeue_response()
{
	static std::string lastWord = "";

	if (_responseQueue.size() == 0)
	{
		size_t receivedBytes = receive_data();

		if (receivedBytes != 0)
		{
			auto begin = _buffer;
			auto end   = _buffer + receivedBytes - 1;
			do
			{
				auto it = std::find_if(begin, end, [](char x) { return x == '\0';});
				if (lastWord != "")
				{
					lastWord += std::string(begin);
					_responseQueue.push(lastWord);
					lastWord = "";
				}
				if (it == end)
				{
					try
					{
						std::string result(begin);
						json::parse(result);
						_responseQueue.push(result);
					}
					catch (const json::parse_error& e)
					{
						lastWord = std::string(begin);
					}
					break;
				}
				else
				{
					_responseQueue.push(std::string(begin));
					begin = it + 1;
				}
			} while(1);
		}
	}

	if (_responseQueue.size() == 0)
		return "";

	std::string result = _responseQueue.front();
	_responseQueue.pop();
	return result;
}

// receive data from server.
size_t Server::receive_data()
{
	int receivedBytes = 0;
	receivedBytes = recv(_socket, _buffer, BUFFER_SIZE - 1, 0);
	
	if (receivedBytes < 0)
	{
		if (errno != EWOULDBLOCK && errno != EAGAIN)
		{
			std::cerr << "recv failed: " << strerror(errno) << std::endl;
		}
		return 0;
	}
	else if (receivedBytes == 0)
	{
		std::cerr << "Server is unavailable.\n";
		exit(-1);
	}
	return receivedBytes;
}

// make socket - non-blocking.
int set_non_blocking(int sock)
{
        int flags = fcntl(sock, F_GETFL, 0);
        return fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

// parse JSON.
// sometimes JSONs come together. For instance, "{"Name":"Ivan"}{"Name":"Vladimir"}"
// this function just split such JSONs.
std::vector<std::string> splitJson(const std::string& input) {
    std::vector<std::string> jsonObjects;
    int braceCount = 0;
    size_t start = 0;

    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '{') {
            if (braceCount == 0) {
                start = i; // Mark the start of a new JSON object
            }
            braceCount++;
        } else if (input[i] == '}') {
            braceCount--;
            if (braceCount == 0) {
                // We found a complete JSON object
                jsonObjects.push_back(input.substr(start, i - start + 1));
            }
        }
    }

    return jsonObjects;
}

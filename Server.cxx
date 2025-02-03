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

extern std::string username;
extern U32 userID;

int set_non_blocking(int);
std::vector<std::string> splitJson(const std::string&);

// contructor.
Server::Server(const std::string& addr, U16 port)
{
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
		std::cout << "RESPONSE : " << response << '\n';
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
			std::cerr << "Server creation response exception ; Parse error at byte : " << e.byte << " : " << e.what() << '\n';
		}
		catch (const json::type_error& e)
		{
			std::cerr << "Server creation response : exception ; Type error : " << e.what() << '\n';
		}
		catch (const json::out_of_range& e)
		{
			std::cerr << "Server creation response : exception ; Out of range error : " << e.what() << '\n';
		}
	}
}

// Server's destructor.
Server::~Server()
{
	// just close socket.
	close(_socket);
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
	//std::string responce = receive_data();
	//j = json::parse(responce);
	//return j["room-id"];
	return 0;
}

// connect to an existing room.
bool Server::connect_to_room(I32 id)
{
	json j;
	j["Command"] = "ConnectToRoom";
	//send_data(j.dump());
	return false;
}

// make me ready.
void Server::make_ready()
{
	json j;
	j["Command"] = "BeReady";
	j["IsReady"] = "Yes";
	send_data(j.dump());
}

// make me non-ready.
void Server::make_non_ready()
{
	json j;
	j["Command"] = "BeReady";
	j["IsReady"] = "No";
	send_data(j.dump());
}

// send data to server.
void Server::send_data(const std::string& str)
{
	int totalSent = 0;
	while (totalSent < str.size())
	{
		int bytesSent = send(_socket, str.c_str(), str.size() + 1, 0);
		if (bytesSent < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				std::cout << "Send would block, try again later." << std::endl;
			} else {
				std::cerr << "Error sending data: " << strerror(errno) << std::endl;
			}
		} else {
			totalSent += bytesSent;
			std::cout << "Sent " << bytesSent<<" bytes: " << str << std::endl;
		}
	}
}

// dequeue response.
std::string Server::dequeue_response()
{
	std::string received = "";
	do
	{
		received = receive_data();
	} while(received == "");
	
	std::vector<std::string> vec = splitJson(received);
	for (auto& x : vec)
		_responseQueue.push(x);
	
	std::string result = _responseQueue.front();
	_responseQueue.pop();
	return result;
}

// receive data from server.
std::string Server::receive_data()
{
	size_t sizeOfBuffer = 2048;
	char* buffer = new char[sizeOfBuffer];
	int receivedBytes;
	
	receivedBytes = recv(_socket, buffer, sizeOfBuffer - 1, 0);
	
	if (receivedBytes < 0)
	{
		if (errno != EWOULDBLOCK && errno != EAGAIN)
		{
			std::cerr << "recv failed: " << strerror(errno) << std::endl;
			delete buffer;
			return "";
		}
		delete buffer;
		return "";
	}
	else if (receivedBytes == 0)
	{
		std::cerr << "Server is unavailable.\n";
		exit(-1);
	}
	
	buffer[receivedBytes] = 0;
	if (receivedBytes == 0)
	{
		delete buffer;
		return "";
	}
	std::string result(buffer);
	delete buffer;
	return result;
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

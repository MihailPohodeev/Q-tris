#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Server.hxx"
#include "json.hpp"

// contructor.
Server::Server(const std::string& addr, U16 port)
{
	_port = port;
	_address = addr;
	_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (_socket < 0)
	{
		std::cerr << "Server socket creation error!\n";
		//exit();
	}

	sockaddr_in server_addr;
	std::memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_pton(AF_INET, addr.c_str(), &server_addr.sin_addr);

	if (connect(_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		std::cerr << "Server connection error!\n";
	}
}

std::string Server::create_room(const std::string& name)
{
	json j;
	j["type"] = "create-room";
	j["username"] = name;
	send_data(j.dump());
	std::string responce = receive_data();
	j = json::parse(responce);
	return j["room-id"];
}

void Server::connect_to_room(const std::string& id, const std::string& name)
{
	json j;
	j["type"] = "connect-to-room";
	j["room-id"] = id;
	j["username"] = name;
	send_data(j.dump());
}

// send data to server.
void Server::send_data(const std::string& str)
{
	std::cout << "Send size : " << str.size() + 1 << '\n';
	send(_socket, str.c_str(), str.size() + 1, 0);
}

// receive data from server.
std::string Server::receive_data()
{
	char buffer[8096];
	size_t size;
	size = recv(_socket, buffer, 8096, 0);
	return std::string(buffer);
}

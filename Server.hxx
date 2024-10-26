#ifndef _SERVER_HXX_
#define _SERVER_HXX_

#include <string>
#include "setup.hxx"
#include "json.hpp"

using json = nlohmann::json;

class Server
{
	I32 _socket;
	std::string _address;
	U16 _port;
public:
	// constructor.
	// get ip-address and port.
	Server(const std::string&, U16);
	// send data to server.
	void send_data(const std::string&);
	// receive data from server.
	std::string receive_data();
	// destructor.
	//~Server();
};

#endif

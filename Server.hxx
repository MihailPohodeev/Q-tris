#ifndef _SERVER_H_
#define _SERVER_H_

#include <string>
#include "setup.hxx"

class Server
{
	std::string ip_address;
	U16 port;
public:
	// constructor.
	// get ip-address and port.
	Server(const std::string&, U16);
	~Server();
};

#endif

#ifndef _SERVER_HXX_
#define _SERVER_HXX_

#include <string>
#include <queue>
#include "setup.hxx"
#include "json.hpp"

using json = nlohmann::json;

struct GameParameter
{
	U8 playersCount;
	U8 startLevel;
	bool isSameQueue;
};

class Server
{
	I32 _socket;
	std::string _address;
	U16 _port;
	std::queue<std::string> _responseQueue;

	// dequeue response.
	std::string dequeue_response();
public:
	// constructor.
	// get ip-address and port.
	Server(const std::string&, U16);
	// create room.
	I32 create_room(const GameParameter&);
	// connect to room.
	bool connect_to_room(I32);
	// disconnect from server.
	void disconnect();
	// make me ready.
	void make_ready();
	// make me non ready.
	void make_non_ready();
	// loose game.
	void loose_game();
	// send data to server.
	void send_data(const std::string&);
	// receive data from server.
	std::string receive_data();
	// destructor.
	~Server();
};

#endif

#ifndef _SERVER_HXX_
#define _SERVER_HXX_

#include <string>
#include <queue>
#include <mutex>

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
	char* _buffer;
	mutable std::mutex _sendingDataGuard;

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
	// get room's parameters.
	void get_room_parameters();
	// make me ready.
	void make_ready();
	// make me non ready.
	void make_non_ready();
	// request rooms list.
	void get_rooms_list();
	// loose game.
	void loose_game();
	// send data to server.
	bool send_data(const std::string&);
	// receive data from server.
	size_t receive_data();
	// dequeue response.
	std::string dequeue_response();
	// destructor.
	~Server();
};

#endif

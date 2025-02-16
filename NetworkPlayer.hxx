#ifndef _NETWORK_PLAYER_HXX_
#define _NETWORK_PLAYER_HXX_

#include <string>

#include "PlayerObject.hxx"

class NetworkPlayer : public PlayerObject
{
	I32 _userID;
	std::string _username;
	std::string _dataFrameString;
	U8 _nextFigureIndex;
public:
	// constructor.
	NetworkPlayer(I32);
	// destructor.
	virtual ~NetworkPlayer() {}
	// update game proccess.
	void update() override;
	// exchange data with server.
	void exchange_data() override;
	// get user's id.
	I32 get_ID() const;
	// set user's id.
	void set_ID(I32);
	// get username.
	std::string get_username() const;
	// set username.
	void set_username(const std::string&);
	// set data frame string.
	void set_data_frame_string(const std::string&);
	// get next index of figure.
	U8 get_next_figure_index() override;
};

#endif

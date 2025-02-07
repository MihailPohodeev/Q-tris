#ifndef _NETWORK_PLAYER_HXX_
#define _NETWORK_PLAYER_HXX_

#include "PlayerObject.hxx"

class NetworkPlayer : public PlayerObject
{
	I32 _userID;
public:
	// constructor.
	NetworkPlayer(I32);
	// update game proccess.
	void update() override;
	// exchange data with server.
	void exchange_data() override;
	// get user's id.
	I32 get_ID() const;
};

#endif

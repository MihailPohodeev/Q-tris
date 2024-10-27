#ifndef _NETWORK_PLAYER_HXX_
#define _NETWORK_PLAYER_HXX_

#include "PlayerObject.hxx"

class NetworkPlayer : public PlayerObject
{
public:
	// constructor.
	NetworkPlayer();
	// update game proccess.
	void update() override;
	// exchange data with server.
	void exchange_data() override;
};

#endif

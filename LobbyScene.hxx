#ifndef _LOBBY_SCENE_HXX_
#define _LOBBY_SCENE_HXX_

#include <list>

#include "PlayerObject.hxx"
#include "NetworkPlayer.hxx"

class LobbyScene
{
	std::list<NetworkPlayer*> _users;
public:
	LobbyScene(U8);
};

#endif

#ifndef _MULTIPLAYER_SCENE_
#define _MULTIPLAYER_SCENE_

#include <vector>
#include <string>
#include <exception>

#include "Scene.hxx"
#include "RealPlayer.hxx"
#include "NetworkPlayer.hxx"
#include "Window.hxx"

class MultiplayerScene : public Scene
{
	Controller* _controller;
	RealPlayer* _realPlayer;
	std::vector<NetworkPlayer*> _netPlayers;
	std::vector<Window*> _windows;

public:
	// constructor.
	// parameters: players count, isSameQueue, start level.
	MultiplayerScene(U8, bool, U8);
	void update() override;
	void render() const override;
	void exchange_data() override;
	~MultiplayerScene();
};

// exception: too few players for creation scene.
class TooFewPlayersException : public std::exception
{
private:
	std::string message;
public:
	TooFewPlayersException(const std::string& msg) : message(msg) {}
	TooFewPlayersException(U8 playersCount) : message("few players count argument : 2 <= players count <= 4 ; received : " + std::to_string(static_cast<U32>(playersCount))) {}
	virtual const char* what() const noexcept override
	{
		return message.c_str();
	}
};

// exception: too many players for creation scene.
class TooManyPlayersException : public std::exception
{
private:
	std::string message;
public:
	TooManyPlayersException(U8 playersCount) : message("too many players count argument! expected : 2 <= players count <= 4; received : " + std::to_string(static_cast<U32>(playersCount))) {}
	virtual const char* what() const noexcept override
        {
                return message.c_str();
        }
};

#endif

#include <SFML/Graphics.hpp>

#include "Server.hxx"
#include "MultiplayerScene.hxx"
#include "KeyboardController1.hxx"
#include "NetworkPlayer.hxx"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;
extern bool isReady;
extern I32 userID;
extern Server* server;
extern sf::RenderWindow* window;

MultiplayerScene::MultiplayerScene(U8 playersCount, bool isSameQueue, U8 startLevel) : _windows(playersCount)
{
	// check if players count is unavalible.
	if (playersCount < 2)
		throw TooFewPlayersException(playersCount);
	else if (playersCount > 4)
		throw TooManyPlayersException(playersCount);
	
	// create controller and real player.
	_controller = new KeyboardController1();
	_realPlayer = new RealPlayer();
	_realPlayer->set_controller(_controller);

	sf::Vector2f mainWindowSize = sf::Vector2f(SCR_HEIGHT * 0.7, SCR_HEIGHT * 0.7);
	_windows[0] = new Window(mainWindowSize);
	int offset = (SCR_HEIGHT - mainWindowSize.x) * 0.5;
	_windows[0]->set_player_object(_realPlayer);
	_windows[0]->set_position(sf::Vector2f(offset * 0.5, offset));

	U8 netPlayersCount = playersCount - 1;
	if (SCR_WIDTH / (float)SCR_HEIGHT < 1.5f)
	{
		float xSize = SCR_WIDTH - (mainWindowSize.x + offset);
		xSize = xSize * 0.9;
		float ySize = (mainWindowSize.y / netPlayersCount) * 0.9;
		float minimalSize = xSize < ySize ? xSize : ySize;
		sf::Vector2f netWindowSize(minimalSize, minimalSize);

		float posX = (mainWindowSize.x + offset + SCR_WIDTH - minimalSize) / 2;
		for (U8 i = 1; i < _windows.size(); i++)
		{
			_windows[i] = new Window(netWindowSize);
			NetworkPlayer* netPlayer = new NetworkPlayer(0);
			_netPlayers.push_back(netPlayer);
			_windows[i]->set_player_object(netPlayer);

			float smallOffset = mainWindowSize.y - minimalSize * netPlayersCount;
			smallOffset /= (netPlayersCount + 1);
			_windows[i]->set_position(sf::Vector2f(posX, offset \
					+ smallOffset * i + minimalSize * (i - 1)));
		}
	}
	else
	{
		float size = SCR_WIDTH - (mainWindowSize.x + offset);
		size /= netPlayersCount;
		size *= 0.9;
		if (size > mainWindowSize.x)
			size = mainWindowSize.x;
		sf::Vector2f netWindowsSize(sf::Vector2f(size, size));

		float smallOffset = SCR_WIDTH - (mainWindowSize.x + offset);
		smallOffset -= size * netPlayersCount;
		smallOffset /= netPlayersCount + 1;
		float posX = mainWindowSize.x + offset;
		float posY = (SCR_HEIGHT - size) / 2;
		for (U8 i = 1; i < _windows.size(); i++)
		{
			_windows[i] = new Window(netWindowsSize);
			NetworkPlayer* netPlayer = new NetworkPlayer(0);
			_netPlayers.push_back(netPlayer);
			_windows[i]->set_player_object(netPlayer);
			_windows[i]->set_position(sf::Vector2f(posX + size * (i - 1) + smallOffset * i, posY));
		}
	}

	server->get_room_parameters();
	do
	{
		std::string response = server->dequeue_response();
		if (response == "")
			continue;
		json responseJSON;
		try
		{
			responseJSON = json::parse(response);
			std::string command = responseJSON["Command"];
			if (command != "RoomParameters")
				continue;
			json users = responseJSON["Users"];
			auto iter = _netPlayers.begin();
			for(const auto& user : users)
			{
				(*iter)->set_ID(user["ID"]);
				(*iter)->set_username(user["Username"]);
				++iter;
			}
			break;

		}
		catch(const json::parse_error& e)
		{
			std::cerr << "Can't get room's parameters ; Parse error at byte : " << e.byte << " : " << e.what() << " ; String : " << response<< '\n';
			exit(-1);
		}
		catch (const json::type_error& e)
		{
			std::cerr << "Can't get room's parameters ; Type error : " << e.what() << " ; String : " << response << '\n';
			exit(-1);
		}
		catch (const json::out_of_range& e)
		{
			std::cerr << "Can't get room's parameters ; Out of range error : " << e.what() << " ; String : " << response << '\n';
			exit(-1);
		}
	} while(1);

}

MultiplayerScene::~MultiplayerScene()
{
	delete _realPlayer;
	delete _controller;
	for (auto it = _netPlayers.begin(); it != _netPlayers.end(); ++it)
	{
		if (*it)
			delete *it;
	}
	for (auto it = _windows.begin(); it != _windows.end(); ++it)
	{
		if (*it)
			delete *it;
	}
}

void MultiplayerScene::update()
{
	static bool isEnterPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		if (!isEnterPressed)
		{
			if (isReady)
				server->make_non_ready();
			else
				server->make_ready();
		}
		isEnterPressed = true;
	}
	else
		isEnterPressed = false;

	for (U8 i = 0; i < _windows.size(); i++)
		_windows[i]->update();
}

void MultiplayerScene::render() const
{
	for (U8 i = 0; i < _windows.size(); i++)
		if (_windows[i])
			_windows[i]->render();
}

void MultiplayerScene::exchange_data()
{
	while(window->isOpen())
	{
		_realPlayer->exchange_data();
		std::string dataFrame = server->dequeue_response();
		if (dataFrame != "")
		{
			json responseJSON;
			try
			{
				responseJSON = json::parse(dataFrame);
				std::string command = responseJSON["Command"];

				if (command == "DataFrame")
				{
					json arrayData = responseJSON["Data"];
					for (const auto& frame : arrayData)
					{
						I32 id = frame["UserID"];
						if (id == userID)
							continue;

						auto user = std::find_if(_netPlayers.begin(), _netPlayers.end(), \
								[id](NetworkPlayer* np) \
								{return np->get_ID() == id;});
						if (user == _netPlayers.end())
						{
							std::cerr << "No such user ; ID : " << frame["UserID"] << '\n';
						}
						else
						{
							(*user)->set_data_frame_string(frame["Data"].dump());
						}
					}
				}
			}
			catch(const json::parse_error& e)
			{
				std::cerr << "Network Frames handling error ; Parse error at byte : " << e.byte << " : " << e.what() << " ; String : " << dataFrame << '\n';
			}
			catch (const json::type_error& e)
			{
				std::cerr << "Network Frames handling error ; Type error : " << e.what() << " ; String : " << dataFrame << '\n';
			}
			catch (const json::out_of_range& e)
			{
				std::cerr << "Network Frames handling error ; Out of range error : " << e.what() << " ; String : " << dataFrame << '\n';
			}

			for (auto it = _netPlayers.begin(); it != _netPlayers.end(); ++it)
			{
				if (*it)
				{
					(*it)->exchange_data();
				}
			}
		}
	}
}

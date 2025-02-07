#include <iostream>
#include <fstream>
#include <cstdlib>
#include <thread>

#include "json.hpp"
#include "Figures/Element.hxx"
#include "Matrix.hxx"
#include "GameField.hxx"
#include "Figures/O_Figure.hxx"
#include "Figures/I_Figure.hxx"
#include "Figures/J_Figure.hxx"
#include "Figures/L_Figure.hxx"
#include "Figures/T_Figure.hxx"
#include "Figures/S_Figure.hxx"
#include "Figures/Z_Figure.hxx"
#include "ScoreTable.hxx"
#include "KeyboardController1.hxx"
#include "JoystickController.hxx"
#include "Window.hxx"
#include "RealPlayer.hxx"
#include "NetworkPlayer.hxx"
#include "Server.hxx"
#include "Scene.hxx"
#include "UI/MainMenu.hxx"
#include "MultiplayerScene.hxx"
#include "functions.hxx"

using json = nlohmann::json;

sf::RenderWindow* window;
sf::Font* mainFont;

Figure** figuresArray;
Server* server;
Scene* currentScene;

int SCR_WIDTH  = 800;
int SCR_HEIGHT = 450;

std::string username;
I32 userID;
bool isReady = false;

int main(int argc, char** argv)
{
	srand(time(0));
	// server initialization.	
	std::ifstream configStream("config.json");
	if (!configStream.is_open()) {
		std::cerr << "Could not open the config file!" << std::endl;
		return 1;
	}

	json config;

	try
	{
		configStream >> config;
	}
	catch (const json::parse_error& e)
	{
		std::cerr << "Parse error : " << e.what() << '\n';
		return 1;
	}

	std::string ipAddress;
	U16 port;
	U8 playerCount = 0;
	try
	{
		ipAddress = config["Server"]["IPAddress"];
		port = config["Server"]["Port"];
		playerCount = config["Client"]["PlayersCount"];
		username = config["Player"]["Username"];
		if (argc >= 4)
			username = std::string(argv[3]);

	}
	catch (const json::type_error& e)
	{
		std::cerr << "Errors in config.json file : " << e.what() << '\n';
	}

	server = new Server(ipAddress, port);

	// window initialization.
	// sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	// SCR_WIDTH = desktop.width;
	// SCR_HEIGHT = desktop.height;
	// window = new sf::RenderWindow(desktop, "Q-tris", sf::Style::Fullscreen);
	window = new sf::RenderWindow(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Q-tris");

	// font initialization.
	mainFont = new sf::Font;
	mainFont->loadFromFile("Fonts/GASAGRANDE.ttf");

	// array with figures init.
	figuresArray = new Figure*[7];
	figuresArray[0] = new O_Figure();
	figuresArray[1] = new J_Figure();
	figuresArray[2] = new L_Figure();
	figuresArray[3] = new I_Figure();
	figuresArray[4] = new T_Figure();
	figuresArray[5] = new S_Figure();
	figuresArray[6] = new Z_Figure();

	figuresArray[0]->set_color(sf::Color(0, 255, 0, 255));
	figuresArray[1]->set_color(sf::Color(255, 0, 0, 255));
	figuresArray[2]->set_color(sf::Color(0, 0, 255, 255));
	figuresArray[3]->set_color(sf::Color(255, 255, 0, 255));
	figuresArray[4]->set_color(sf::Color(0, 255, 255, 255));
	figuresArray[5]->set_color(sf::Color(255, 0, 255, 255));
	figuresArray[6]->set_color(sf::Color(200, 128, 128, 255));

	struct GameParameter gp {2, 1, true};
	if (argc >= 3)
	{
		if (std::string(argv[1]) == "connect-to-room")
		{
			try
			{
				I32 roomID = std::stoi(std::string(argv[2]));
				if (server->connect_to_room(roomID))
					std::cout << "Successful connected to the room.\n";
				else
				{
					std::cout << "Failed to connect to the room.\n";
					exit(-1);
				}
			}
			catch (const std::invalid_argument& e) 
			{
				std::cerr << "Invalid argument: " << e.what() << std::endl;
			}
			catch (const std::out_of_range& e) 
			{
				std::cerr << "Out of range: " << e.what() << std::endl;
			}
		}
		else
		{
			std::cerr << "Unknown command!!!\n";
			exit(-1);
		}
	}
	else
	{
		I32 roomID = server->create_room(gp);
		std::cout << "Room_ID : " << roomID << '\n';
	}
	server->make_ready();
	
	/*
	KeyboardController1 controller;
	KeyboardController1 controller1;
	JoystickController joyControll(0);
	
	RealPlayer rp;
	NetworkPlayer np;
	rp.set_controller(&controller);

	Window realWin(sf::Vector2f(500.f, 500.f));
	realWin.set_player_object(&rp);
	realWin.set_position(sf::Vector2f(150.f, 50.f));
	
	Window netWin(sf::Vector2f(300.f, 300.f));
	netWin.set_player_object(&np);
	netWin.set_position(sf::Vector2f(400.f, 100.f));

	//Scene* currentScene = new MainMenu();
	
	MultiplayerScene multiplayerScene(playerCount, true, 0);
	*/

	do
	{
		std::string response = server->dequeue_response();
		if (response == "")
			continue;
		std::cout << "response of game starting : " << response << '\n';
		json responseJSON;
		try
		{
			responseJSON = json::parse(response);
			if (responseJSON["Command"] != "CanStartGame")
				continue;
			break;
		}
		catch(const json::parse_error& e)
		{
			std::cerr << "Game Start response exception ; Parse error at byte : " << e.byte << " : " << e.what() << " ; String : " << response << '\n';
		}
		catch (const json::type_error& e)
		{
			std::cerr << "Game Start response exception ; Type error : " << e.what() << " ; String : " << response << '\n';
		}
		catch (const json::out_of_range& e)
		{
			std::cerr << "Game Start response exception ; Out of range error : " << e.what() << " ; String : " << response << '\n';
		}
	} while(1);

	MultiplayerScene multiplayerScene(playerCount, true, 0);
	currentScene = &multiplayerScene;
	
	std::cout << "start game : \n";
	std::thread dataTransferThread(&MultiplayerScene::exchange_data, &multiplayerScene);
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		//server.send_data("Looser");
		//std::string message = server.receive_data();
		//std::cout << message << '\n';
		//realWin.update();
		//realWin.render();
		window->clear();
		multiplayerScene.update();
		multiplayerScene.render();
		window->display();
	}
	dataTransferThread.join();

	for (U8 i = 0; i < 7; i++)
		delete figuresArray[i];
	//delete currentScene;
	delete [] figuresArray;
	delete mainFont;
	delete server;
	delete window;
	return 0;
}

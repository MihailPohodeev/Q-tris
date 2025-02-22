#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

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
#include "SinglePlayerScene.hxx"
#include "functions.hxx"
#include "UI/CreateRoomMenu.hxx"

using json = nlohmann::json;

sf::RenderWindow* window;
sf::Font* mainFont;

Figure** figuresArray;
Server* server;
Scene* currentScene;
Scene* nextScene;
std::mutex currentSceneGuard;

int SCR_WIDTH  = 800;
int SCR_HEIGHT = 450;

std::string username;
std::string modeQueue = "Different";
I32 userID;
bool isReady = false;

int main(int argc, char** argv)
{
	srand(time(0));
	// server initialization.	

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

	//struct GameParameter gp {playersCount, 1, true};
	// if (argc >= 3)
	// {
	// 	if (std::string(argv[1]) == "connect-to-room")
	// 	{
	// 		try
	// 		{
	// 			I32 roomID = std::stoi(std::string(argv[2]));
	// 			if (server->connect_to_room(roomID))
	// 				std::cout << "Successful connected to the room.\n";
	// 			else
	// 			{
	// 				std::cout << "Failed to connect to the room.\n";
	// 				exit(-1);
	// 			}
	// 		}
	// 		catch (const std::invalid_argument& e) 
	// 		{
	// 			std::cerr << "Invalid argument: " << e.what() << std::endl;
	// 		}
	// 		catch (const std::out_of_range& e) 
	// 		{
	// 			std::cerr << "Out of range: " << e.what() << std::endl;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		std::cerr << "Unknown command!!!\n";
	// 		exit(-1);
	// 	}
	// }
	// else
	// {
	// 	I32 roomID = server->create_room(gp);
	// 	std::cout << "Room_ID : " << roomID << '\n';
	// }

	// server->make_ready();

	// do
	// {
	// 	std::string response = server->dequeue_response();
	// 	if (response == "")
	// 		continue;
	// 	std::cout << "response of game starting : " << response << '\n';
	// 	json responseJSON;
	// 	try
	// 	{
	// 		responseJSON = json::parse(response);
	// 		if (responseJSON["Command"] != "CanStartGame")
	// 			continue;
	// 		break;
	// 	}
	// 	catch(const json::parse_error& e)
	// 	{
	// 		std::cerr << "Game Start response exception ; Parse error at byte : " << e.byte << " : " << e.what() << " ; String : " << response << '\n';
	// 	}
	// 	catch (const json::type_error& e)
	// 	{
	// 		std::cerr << "Game Start response exception ; Type error : " << e.what() << " ; String : " << response << '\n';
	// 	}
	// 	catch (const json::out_of_range& e)
	// 	{
	// 		std::cerr << "Game Start response exception ; Out of range error : " << e.what() << " ; String : " << response << '\n';
	// 	}
	// } while(1);

	//MultiplayerScene multiplayerScene(playersCount, true, 0);
	//currentScene = &multiplayerScene;
	currentScene = new MainMenu();
	
	std::cout << "start game : \n";
	std::thread dataTransferThread([](){while(window->isOpen()) { std::lock_guard<std::mutex> lock(currentSceneGuard); currentScene->exchange_data();}});
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			tgui::Gui* gui = currentScene->get_gui_ptr();
			if (gui)
			{
				gui->handleEvent(event);
			}
			if (nextScene)
			{
				std::lock_guard<std::mutex> lock(currentSceneGuard);
				std::cout << "destroy current scene!\n";
				delete currentScene;
				currentScene = nextScene;
				nextScene = nullptr;
			}
		}

		window->clear();
		currentScene->update();
		currentScene->render();
		window->display();
	}
	dataTransferThread.join();

	for (U8 i = 0; i < 7; i++)
		delete figuresArray[i];
	delete currentScene;
	delete [] figuresArray;
	delete mainFont;
	delete server;
	delete window;
	return 0;
}

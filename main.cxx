#include <iostream>
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
#include "Server.hxx"

extern sf::RenderWindow* window;
sf::Font* mainFont;

Figure** figuresArray;
Server server("127.0.0.1", 18881);

int main(int argc, char** argv)
{
	int SCR_WIDTH =  800;
	int SCR_HEIGHT = 600;
	window = new sf::RenderWindow(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Q-tris");

	mainFont = new sf::Font;
	mainFont->loadFromFile("Fonts/GASAGRANDE.ttf");

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

	std::cout << "All painted!\n";

	KeyboardController1 controller;
	JoystickController joyControll(0);

	RealPlayer rp;
	rp.set_controller(&controller);

	Window realWin(sf::Vector2f(400.f, 400.f));
	realWin.set_player_object(&rp);
	realWin.set_position(sf::Vector2f(200.f, 100.f));

	if (strcmp(argv[1], "create-room") == 0)
	{
		json createRoom;
		createRoom["type"] = "create-room";
		createRoom["username"] = "KalKalich";
		server.send_data(createRoom.dump());
		std::string responce = server.receive_data();
		std::cout << "responce : " << responce << '\n';
	}
	else if (strcmp(argv[1], "connect-to-room") == 0)
	{
		json connectToRoom;
		connectToRoom["type"] = "connect-to-room";
		connectToRoom["room-id"] = argv[2];
		connectToRoom["username"] = "Second Dodick";
		std::cout << connectToRoom.dump() << '\n';
		server.send_data(connectToRoom.dump());
		std::string responce = server.receive_data();
		std::cout << "responce : " << responce << '\n';
	}

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

		realWin.update();

		window->clear();
		realWin.render();
		window->display();
	}

	for (U8 i = 0; i < 4; i++)
		delete figuresArray[i];
	delete figuresArray;
	delete mainFont;
	delete window;
	return 0;
}

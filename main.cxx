#include <iostream>
#include "Figures/Element.hxx"
#include "Matrix.hxx"
#include "GameField.hxx"
#include "Figures/O_Figure.hxx"
#include "Figures/I_Figure.hxx"
#include "Figures/J_Figure.hxx"
#include "Figures/L_Figure.hxx"
#include "ScoreTable.hxx"
#include "KeyboardController1.hxx"
#include "JoystickController.hxx"
#include "Window.hxx"
#include "RealPlayer.hxx"

extern sf::RenderWindow* window;
sf::Font* mainFont;

Figure** figuresArray;

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

	figuresArray[0]->set_color(sf::Color(0, 255, 0, 255));
	figuresArray[1]->set_color(sf::Color(255, 0, 0, 255));
	figuresArray[2]->set_color(sf::Color(0, 0, 255, 255));
	figuresArray[3]->set_color(sf::Color(128, 128, 0, 255));

	std::cout << "All painted!\n"	;

	KeyboardController1 controller;

	RealPlayer rp;
	rp.set_controller(&controller);

	Window realWin(sf::Vector2f(400.f, 400.f));
	realWin.set_player_object(&rp);
	realWin.set_position(sf::Vector2f(200.f, 100.f));

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

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

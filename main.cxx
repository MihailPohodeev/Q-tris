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

extern sf::RenderWindow* window;
sf::Font* mainFont;

int main(int argc, char** argv)
{
	int SCR_WIDTH =  800;
	int SCR_HEIGHT = 600;
	window = new sf::RenderWindow(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Q-tris");

	mainFont = new sf::Font;
	mainFont->loadFromFile("Fonts/GASAGRANDE.ttf");

	//sf::CircleShape shape(100);
	
	//mat.add_element({sf::Color(128, 200, 255, 255), sf::Vector2i(5, 5)});
	

	ScoreTable sc(sf::Vector2f(200, 400));
	sc.set_position(sf::Vector2f(300, 100));
	
	KeyboardController1 controller;
	JoystickController joystick(0);

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		if (joystick.is_drop())
			std::cout << "drop\n";
		if (joystick.is_accelerate())
			std::cout << "accelerate\n";
		if (joystick.is_rotate_right())
			std::cout << "rotate-right\n";
		if (joystick.is_rotate_left())
			std::cout << "rotate-left\n";
		if (joystick.is_move_right())
			std::cout << "right\n";
		if (joystick.is_move_left())
			std::cout << "left\n";

		window->clear();
		sc.render();
		window->display();
	}
	delete mainFont;
	delete window;
	return 0;
}

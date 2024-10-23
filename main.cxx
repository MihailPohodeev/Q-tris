#include <iostream>
#include "Element.hxx"
#include "Matrix.hxx"
#include "GameField.hxx"
#include "O_Figure.hxx"

extern sf::RenderWindow* window;

int main(int argc, char** argv)
{
	int SCR_WIDTH =  800;
	int SCR_HEIGHT = 600;
	window = new sf::RenderWindow(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Q-tris");
	
	//sf::CircleShape shape(100);
	
	Matrix mat;
	//mat.add_element({sf::Color(128, 200, 255, 255), sf::Vector2i(5, 5)});

	O_Figure O;
	O.set_color(sf::Color(230, 180, 100, 255));
	O.set_position(sf::Vector2i(5, 5));
	mat.add_figure(O);

	GameField gField(sf::Vector2f(200, 400));
	gField.set_matrix(mat);

	Element elem(sf::Vector2f(50, 50));

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		gField.render();
		window->display();
	}
	return 0;
}

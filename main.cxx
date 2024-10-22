#include <iostream>
#include "Element.hxx"

extern sf::RenderWindow* window;

int main(int argc, char** argv)
{
	int SCR_WIDTH =  800;
	int SCR_HEIGHT = 600;
	window = new sf::RenderWindow(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Q-tris");
	
	//sf::CircleShape shape(100);

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
		elem.render();
		window->display();
	}
	return 0;
}

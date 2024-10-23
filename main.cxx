#include <iostream>
#include "Figures/Element.hxx"
#include "Matrix.hxx"
#include "GameField.hxx"
#include "Figures/O_Figure.hxx"
#include "Figures/I_Figure.hxx"
#include "Figures/J_Figure.hxx"
#include "Figures/L_Figure.hxx"

extern sf::RenderWindow* window;

int main(int argc, char** argv)
{
	int SCR_WIDTH =  800;
	int SCR_HEIGHT = 600;
	window = new sf::RenderWindow(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Q-tris");
	
	//sf::CircleShape shape(100);
	
	Matrix mat;
	//mat.add_element({sf::Color(128, 200, 255, 255), sf::Vector2i(5, 5)});
	
	L_Figure J;
	J.set_position(sf::Vector2i(5, 5));
	J.set_color(sf::Color(200, 255, 180, 255));
	J.rotate_right();
	J.rotate_left();
	mat.add_figure(J);

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

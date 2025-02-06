#include <SFML/Graphics.hpp>

#include "functions.hxx"
#include "Scene.hxx"

extern Scene* currentScene;
extern sf::RenderWindow* window;

void update()
{
	while (window->isOpen())
	{
		currentScene->update();
	}
}

void render()
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		window->clear();
		currentScene->render();
		window->display();
	}
}

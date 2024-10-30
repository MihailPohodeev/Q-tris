#include "MainMenu.hxx"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;
extern sf::RenderWindow* window;

MainMenu::MainMenu() : _exit(sf::Vector2f(200, 50)), _background(sf::Vector2f(SCR_WIDTH, SCR_HEIGHT))
{
	_texture.loadFromFile("Images/sky.jpeg");
	_background.setTexture(&_texture);
	_exit.set_position(sf::Vector2f((SCR_WIDTH -  _exit.get_size().x) / 2, SCR_WIDTH / 2.0));
	_exit.set_string("EXIT");
}

void MainMenu::update()
{

}

void MainMenu::render() const
{
	window->draw(_background);
	_exit.render();
}

void MainMenu::exchange_data()
{

}

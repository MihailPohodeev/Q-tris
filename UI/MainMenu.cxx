#include "MainMenu.hxx"
#include "../MultiplayerScene.hxx"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;
extern sf::RenderWindow* window;
extern Scene* currentScene;

MainMenu::MainMenu() : _gui(*window), _background(sf::Vector2f(SCR_WIDTH, SCR_HEIGHT))
{
	_texture.loadFromFile("Images/sky.jpeg");
	_background.setTexture(&_texture);
	_singlePlayerButton = tgui::Button::create("SinglePlayer");
	_multiPlayerButton = tgui::Button::create("MultiPlayer");
	_settingsButton = tgui::Button::create("Settings");
	_exitButton = tgui::Button::create("Exit");

	int sizeX = SCR_WIDTH / 8;
	int sizeY = sizeX / 4;
	_singlePlayerButton->setSize(sizeX, sizeY);
	_multiPlayerButton->setSize(sizeX, sizeY);
	_settingsButton->setSize(sizeX, sizeY);
	_exitButton->setSize(sizeX, sizeY);

	int posX = (SCR_WIDTH - sizeX) / 2;
	int posY = (SCR_HEIGHT) / 2;
	_singlePlayerButton->setPosition(posX, posY);
	_multiPlayerButton->setPosition(posX, posY + sizeY * 1.5);
	_settingsButton->setPosition(posX, posY + sizeY * 3);
	_exitButton->setPosition(posX, posY  + sizeY * 4.5);

	_multiPlayerButton->onClick([&](){delete currentScene; currentScene = new MultiplayerScene(2, true, 0);});
	_exitButton->onClick([](){exit(-1);});

	_gui.add(_singlePlayerButton);
	_gui.add(_multiPlayerButton);
	_gui.add(_settingsButton);
	_gui.add(_exitButton);
}

void MainMenu::update()
{
	return;
}

tgui::Gui* MainMenu::get_gui_ptr() const
{
	return &_gui;
}

void MainMenu::render() const
{
	_gui.draw();
}

void MainMenu::exchange_data()
{
	return;
}

#include "MultiplayerMenu.hxx"
#include "MainMenu.hxx"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;
extern Scene* nextScene;
extern sf::RenderWindow* window;

MultiplayerMenu::MultiplayerMenu() :  _gui(*window)
{
	_createRoomButton = tgui::Button::create("Create new Room");
	_backButton = tgui::Button::create("Back");

	int sizeX = SCR_WIDTH / 6;
	int sizeY = sizeX / 4;
	_createRoomButton->setSize(sizeX, sizeY);
	_backButton->setSize(sizeX, sizeY);

	int posX = (SCR_WIDTH - sizeX) / 4;
	int posY = (SCR_HEIGHT) * 0.75;
	_createRoomButton->setPosition(posX, posY);
	_backButton->setPosition(posX * 3, posY);

	_createRoomButton->onClick([&](){});
	_backButton->onClick([&](){nextScene = new MainMenu();});

	_gui.add(_createRoomButton);
	_gui.add(_backButton);
}

void MultiplayerMenu::update()
{
    return;
}

void MultiplayerMenu::render() const
{
    _gui.draw();
}

tgui::Gui* MultiplayerMenu::get_gui_ptr() const
{
    return &_gui;
}

void MultiplayerMenu::exchange_data()
{
    return;
}
#include "MainMenu.hxx"
#include "../MultiplayerScene.hxx"
#include "MultiplayerMenu.hxx"
#include "SingleplayerMenu.hxx"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;
extern sf::RenderWindow* window;
extern Scene* nextScene;
extern std::string username;

MainMenu::MainMenu() : _gui(*window), _background(sf::Vector2f(SCR_WIDTH, SCR_HEIGHT))
{
	_texture.loadFromFile("Images/sky.jpeg");
	_background.setTexture(&_texture);
	_usernameLabel = tgui::Label::create("Input your username : ");
	_usernameEditBox = tgui::EditBox::create();
	_singlePlayerButton = tgui::Button::create("SinglePlayer");
	_multiPlayerButton = tgui::Button::create("MultiPlayer");
	_settingsButton = tgui::Button::create("Settings");
	_exitButton = tgui::Button::create("Exit");

	int textSize = (SCR_WIDTH + SCR_HEIGHT) / 80;
	int sizeX = SCR_WIDTH / 8;
	int sizeY = sizeX / 4;
	_usernameLabel->setSize(SCR_WIDTH * 0.25, 25);
	_usernameEditBox->setSize(SCR_WIDTH * 0.2, 25);
	_singlePlayerButton->setSize(sizeX, sizeY);
	_multiPlayerButton->setSize(sizeX, sizeY);
	_settingsButton->setSize(sizeX, sizeY);
	_exitButton->setSize(sizeX, sizeY);

	int posX = (SCR_WIDTH - sizeX) / 2;
	int posY = (SCR_HEIGHT) / 2;
	_usernameLabel->setPosition(SCR_WIDTH * 0.3, posY / 2);
	_usernameEditBox->setPosition(SCR_WIDTH * 0.55, posY * 0.49);
	_singlePlayerButton->setPosition(posX, posY);
	_multiPlayerButton->setPosition(posX, posY + sizeY * 1.5);
	_settingsButton->setPosition(posX, posY + sizeY * 3);
	_exitButton->setPosition(posX, posY  + sizeY * 4.5);

	_usernameLabel->setTextSize(textSize);

	_singlePlayerButton->onClick([&](){nextScene = new SinglePlayerMenu();});
	_multiPlayerButton->onClick([&](){nextScene = new MultiplayerMenu();});
	_exitButton->onClick([](){window->close();});

	_gui.add(_singlePlayerButton);
	_gui.add(_multiPlayerButton);
	_gui.add(_settingsButton);
	_gui.add(_exitButton);
	_gui.add(_usernameLabel);
	_gui.add(_usernameEditBox);
}

void MainMenu::update()
{
	_usernameEditBox->onTextChange([&](const tgui::String& newText) {
        username = newText.toStdString(); // Update the std::string with the new text
    });
}

tgui::Gui* MainMenu::get_gui_ptr() const
{
	return &_gui;
}

void MainMenu::render() const
{
	window->draw(_background);
	_gui.draw();
}

void MainMenu::exchange_data()
{
	return;
}

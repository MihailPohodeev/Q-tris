#include "MultiplayerMenu.hxx"
#include "MainMenu.hxx"
#include "../json.hpp"
#include "../setup.hxx"
#include "../Server.hxx"
#include "CreateRoomMenu.hxx"

#include <fstream>
#include <SFML/Graphics.hpp>

using json = nlohmann::json;

extern int SCR_WIDTH;
extern int SCR_HEIGHT;
extern Scene* nextScene;
extern sf::RenderWindow* window;
extern std::string username;
extern Server* server;

MultiplayerMenu::MultiplayerMenu() :  _gui(*window)
{
	_createRoomButton = tgui::Button::create("Create new Room");
	_backButton = tgui::Button::create("Back");
	_listBox = tgui::ListBox::create();

	int sizeX = SCR_WIDTH / 6;
	int sizeY = sizeX / 4;
	_createRoomButton->setSize(sizeX, sizeY);
	_backButton->setSize(sizeX, sizeY);
	sf::Vector2i listSize = sf::Vector2i(SCR_WIDTH * 0.75, SCR_HEIGHT * 0.5);
	_listBox->setSize(listSize.x, listSize.y);

	int posX = (SCR_WIDTH - sizeX) / 4;
	int posY = (SCR_HEIGHT) * 0.75;
	_createRoomButton->setPosition(posX, posY);
	_backButton->setPosition(posX * 3, posY);
	_listBox->setPosition((SCR_WIDTH - listSize.x) / 2, SCR_HEIGHT * 0.2f);

	_listBox->addItem("Item 1");
    _listBox->addItem("Item 2");
    _listBox->addItem("Item 3");
    _listBox->addItem("Item 4");
    _listBox->addItem("Item 5");
	
	_createRoomButton->onClick([&](){nextScene = new CreateRoomMenu();});
	_backButton->onClick([&](){nextScene = new MainMenu();});

	_gui.add(_createRoomButton);
	_gui.add(_backButton);
	_gui.add(_listBox);

	// server creation.
	std::ifstream configStream("config.json");
	if (!configStream.is_open()) {
		std::cerr << "Could not open the config file!" << '\n';
		exit(-1);
	}

	json config;
	try
	{
		configStream >> config;
	}
	catch (const json::parse_error& e)
	{
		std::cerr << "Parse error : " << e.what() << '\n';
		exit(-1);
	}

	std::string ipAddress;
	U16 port;
	try
	{
		ipAddress = config.at("Server").at("IPAddress");
		port = config.at("Server").at("Port");
		username = config.at("Player").at("Username");
	}
	catch (const json::type_error& e)
	{
		std::cerr << "Errors in config.json file : " << e.what() << '\n';
		exit(-1);
	}

	if (server)
		delete server;

	server = new Server(ipAddress, port);

}

MultiplayerMenu::~MultiplayerMenu()
{
	delete server;
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
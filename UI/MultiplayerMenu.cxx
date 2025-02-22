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
extern Scene *nextScene;
extern sf::RenderWindow *window;
extern std::string username;
extern Server *server;

MultiplayerMenu::MultiplayerMenu() : _gui(*window)
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

	_createRoomButton->onClick([&]()
							   { nextScene = new CreateRoomMenu(); });
	_backButton->onClick([&]()
						 { nextScene = new MainMenu(); });

	_gui.add(_createRoomButton);
	_gui.add(_backButton);
	_gui.add(_listBox);

	_listBox->onItemSelect([&]() {
        // Get the selected item
        std::string selectedItem = _listBox->getSelectedItem().toStdString();
        // Perform an action based on the selected item
        std::cout << "Selected item: " << selectedItem << '\n';
    });

	// server creation.
	if (!server)
	{
		std::ifstream configStream("config.json");
		if (!configStream.is_open())
		{
			std::cerr << "Could not open the config file!" << '\n';
			exit(-1);
		}

		json config;
		try
		{
			configStream >> config;
		}
		catch (const json::parse_error &e)
		{
			std::cerr << "Parse error : " << e.what() << '\n';
			exit(-1);
		}
		configStream.close();

		std::string ipAddress;
		U16 port;
		try
		{
			ipAddress = config.at("Server").at("IPAddress");
			port = config.at("Server").at("Port");
			username = config.at("Player").at("Username");
		}
		catch (const json::type_error &e)
		{
			std::cerr << "Errors in config.json file : " << e.what() << '\n';
			exit(-1);
		}

		if (server)
			delete server;

		server = new Server(ipAddress, port);
	}
}

MultiplayerMenu::~MultiplayerMenu()
{
	return;
}

void MultiplayerMenu::update()
{
	return;
}

void MultiplayerMenu::render() const
{
	_gui.draw();
}

tgui::Gui *MultiplayerMenu::get_gui_ptr() const
{
	return &_gui;
}

void MultiplayerMenu::exchange_data()
{
	if (_clock.getElapsedTime().asMilliseconds() > 2'000)
	{
		server->get_rooms_list();
		_clock.restart();
	}

	std::string response = server->dequeue_response();
	json responseJSON;
	if (response == "")
		return;
	try
	{
		responseJSON = json::parse(response);
		std::string command = responseJSON.at("Command");
		if (command != "RoomsList")
			return;
		_listBox->removeAllItems();
		for (auto& x : responseJSON.at("Data"))
			_listBox->addItem(x.dump());
	}
	catch(const json::parse_error& e)
	{
		std::cerr << "MultiplayerMenu Rooms list getting exception ; Parse error at byte : " << e.byte << " : " << e.what() << '\n';
	}
	catch (const json::type_error& e)
	{
		std::cerr << "MultiplayerMenu Rooms list getting exception ; Type error : " << e.what() << '\n';
	}
	catch (const json::out_of_range& e)
	{
		std::cerr << "MultiplayerMenu Rooms list getting exception ; Out of range error : " << e.what() << '\n';
	}
}
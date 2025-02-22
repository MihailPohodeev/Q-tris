#include "Lobby.hxx"
#include "../Server.hxx"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;
extern Scene* nextScene;
extern sf::RenderWindow* window;
extern Server* server;
extern bool isReady;

Lobby::Lobby() : _gui(*window)
{
    sf::Vector2i buttonSize(SCR_WIDTH / 5, SCR_WIDTH / 20);
    sf::Vector2i buttonPos((SCR_WIDTH - buttonSize.x) / 4, SCR_HEIGHT * 0.75);

    _playersList = tgui::ListBox::create();
    _playersList->setSize(SCR_WIDTH * 0.75, SCR_HEIGHT * 0.5);
    _playersList->setPosition((SCR_WIDTH * 0.25) / 2, SCR_HEIGHT * 0.2);
    _gui.add(_playersList);

    _disconnectButton = tgui::Button::create("Disconnect");
    _disconnectButton->setSize(buttonSize.x, buttonSize.y);
    _disconnectButton->setPosition(buttonPos.x * 3, buttonPos.y);
    _gui.add(_disconnectButton);

    _readyButton = tgui::Button::create("Ready");
    _readyButton->setSize(buttonSize.x, buttonSize.y);
    _readyButton->setPosition(buttonPos.x, buttonPos.y);
    _readyButton->getRenderer()->setBackgroundColor(tgui::Color(255, 0, 0));
    _readyButton->getRenderer()->setBackgroundColorHover(tgui::Color(128, 0, 0));
    _readyButton->getRenderer()->setBackgroundColorDown(tgui::Color(0, 64, 0));
    _readyButton->onClick([&]()
    {
        if (isReady)
        {
            isReady = false;
            _readyButton->getRenderer()->setBackgroundColor(tgui::Color(255, 0, 0));
            _readyButton->getRenderer()->setBackgroundColorHover(tgui::Color(128, 0, 0));
            _readyButton->getRenderer()->setBackgroundColorDown(tgui::Color(0, 64, 0));
            server->make_non_ready();
        }
        else
        {
            isReady = true;
            _readyButton->getRenderer()->setBackgroundColor(tgui::Color(0, 255, 0));
            _readyButton->getRenderer()->setBackgroundColorHover(tgui::Color(0, 128, 0));
            _readyButton->getRenderer()->setBackgroundColorDown(tgui::Color(64, 0, 0));
            server->make_ready();
        }
    });
    _gui.add(_readyButton);
}

void Lobby::update()
{
    return;
}

void Lobby::render() const
{
    _gui.draw();
}

tgui::Gui* Lobby::get_gui_ptr() const
{
    return &_gui;
}

void Lobby::exchange_data()
{
    if (_clock.getElapsedTime().asMilliseconds() > 2'000)
    {
        server->get_room_parameters();
        _clock.restart();
    }
    std::string response = server->dequeue_response();
    if (response == "")
        return;
    try
    {
        json responseJSON = json::parse(response);
        std::string command = responseJSON.at("Command");
        if (command == "RoomParameters")
        {
            _playersList->removeAllItems();
            for (auto& x : responseJSON.at("Data"))
                _playersList->addItem(x.dump());
        }
    }
    catch(const json::parse_error& e)
	{
		std::cerr << "Lobby Rooms list getting exception ; Parse error at byte : " << e.byte << " : " << e.what() << "String : " << response << '\n';
	}
	catch (const json::type_error& e)
	{
		std::cerr << "Lobby Rooms list getting exception ; Type error : " << e.what() << "String : " << response << '\n';
	}
	catch (const json::out_of_range& e)
	{
		std::cerr << "Lobby Rooms list getting exception ; Out of range error : " << e.what() << "String : " << response << '\n';
	}
    
}
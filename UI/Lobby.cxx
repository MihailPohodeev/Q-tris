#include "Lobby.hxx"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;
extern Scene* nextScene;
extern sf::RenderWindow* window;
extern bool isReady;

Lobby::Lobby() : _gui(*window)
{
    sf::Vector2i buttonSize(SCR_WIDTH / 5, SCR_WIDTH / 20);
    sf::Vector2i buttonPos((SCR_WIDTH - buttonSize.x) / 4, SCR_HEIGHT * 0.75);

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
        }
        else
        {
            isReady = true;
            _readyButton->getRenderer()->setBackgroundColor(tgui::Color(0, 255, 0));
            _readyButton->getRenderer()->setBackgroundColorHover(tgui::Color(0, 128, 0));
            _readyButton->getRenderer()->setBackgroundColorDown(tgui::Color(64, 0, 0));
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
    return;
}
#ifndef _LOBBY_HXX_
#define _LOBBY_HXX_

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <string>

#include "../Scene.hxx"

class Lobby : public Scene
{
    mutable tgui::Gui _gui;
    sf::Clock _clock;

    tgui::ListBox::Ptr _playersList;
    tgui::Button::Ptr _disconnectButton;
    tgui::Button::Ptr _readyButton;
public:
    Lobby();
    void update() override;
	void render() const override;
	virtual tgui::Gui* get_gui_ptr() const override;
	void exchange_data() override;
};

#endif
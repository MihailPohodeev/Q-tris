#ifndef _MULTIPLAYER_MENU_HXX_
#define _MULTIPLAYER_MENU_HXX_

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "../Scene.hxx"

class MultiplayerMenu : public Scene
{
	sf::Texture _texture;
	sf::RectangleShape _background;
	mutable tgui::Gui _gui;

	tgui::Button::Ptr _createRoomButton;
	tgui::Button::Ptr _backButton;
public:
    MultiplayerMenu();
	void update() override;
	void render() const override;
	virtual tgui::Gui* get_gui_ptr() const override;
	void exchange_data() override;
};

#endif
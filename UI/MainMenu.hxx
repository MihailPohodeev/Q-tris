#ifndef _MAIN_MENU_HXX_
#define _MAIN_MENU_HXX_

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "../Scene.hxx"
#include "Button.hxx"

class MainMenu : public Scene
{
	sf::Texture _texture;
	sf::RectangleShape _background;
	mutable tgui::Gui _gui;

	tgui::Button::Ptr _singlePlayerButton;
	tgui::Button::Ptr _multiPlayerButton;
	tgui::Button::Ptr _settingsButton;
	tgui::Button::Ptr _exitButton;
public:
	MainMenu();
	void update() override;
	void render() const override;
	virtual tgui::Gui* get_gui_ptr() const override;
	void exchange_data() override;
};

#endif

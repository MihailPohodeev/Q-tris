#ifndef _MAIN_MENU_HXX_
#define _MAIN_MENU_HXX_

#include "../Scene.hxx"
#include "Button.hxx"

class MainMenu : public Scene
{
	sf::Texture _texture;
	sf::RectangleShape _background;
	Button _exit;
public:
	MainMenu();
	void update() override;
	void render() const override;
	void exchange_data() override;
};

#endif

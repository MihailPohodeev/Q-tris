#ifndef _BUTTON_HXX_
#define _BUTTON_HXX_

#include <SFML/Graphics.hpp>

class Button
{
	sf::RectangleShape _shape;
	sf::Text _text;
public:
	Button(const sf::Vector2f&);
	void set_position(const sf::Vector2f&);
	sf::Vector2f get_position() const;
	sf::Vector2f get_size() const;
	void set_string(const std::string&);
	void update();
	void render() const;
};

#endif

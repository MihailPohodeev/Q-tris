#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <SFML/Graphics.hpp>

// struct for unique info of Element.
struct ElementData
{
	sf::Color color;
	sf::Vector2i position;

	struct ElementData* clone() const
	{
		struct ElementData* result = new struct ElementData;
		*(result) = *(this);
		return result;
	}
};


class Element
{
	sf::RectangleShape _shape;
public:
	Element(const sf::Vector2f&);
	void set_color(const sf::Color&);
	sf::Color get_color() const;
	void set_position(const sf::Vector2f&);
	void move(const sf::Vector2f&);
	sf::Vector2f get_size() const;
	void set_size(const sf::Vector2f&);
	Element* clone() const;
	void render() const;
};

#endif

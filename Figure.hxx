#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <SFML/Graphics.hpp>
#include "setup.hxx"
#include "Element.hxx"

class Figure
{
protected:
	// state(color and position) of each element in figure.
	struct ElementData _elements[4];
	// current position of figure.
	sf::Vector2i _position;
	// each position for rotation.
	sf::Vector2i** _rotatePositions;
	// count of indeces of rotate positions.
	U8 _maxRotateIndex;
	// current index of rotate position.
	U8 _currentRotateIndex;
public:
	// constructor.
	Figure();
	// copy-constructor.
	Figure(const Figure&);
	// set new color.
	void set_color(const sf::Color&);
	// get color.
	sf::Color get_color() const;
	// copy array _elements to destination.
	void get_all_elements(struct ElementData*) const;
	// move figure.
	void move(const sf::Vector2i&);
	// set new position of figure.
	void set_position(const sf::Vector2i&);
	// return current position of figure.
	sf::Vector2i get_position() const;
	// rotate left the figure.
	void rotate_left();
	// rotate right the figure.
	void rotate_right();
	// return copy of current figure.
	virtual Figure* clone() const = 0;
	// destructor.
	virtual ~Figure();
};

#endif

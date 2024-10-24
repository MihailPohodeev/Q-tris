#ifndef _GAME_FIELD_H_
#define _GAME_FIELD_H_

#include <SFML/Graphics.hpp>
#include "setup.hxx"
#include "Matrix.hxx"

class GameField
{
	// field for game.
	sf::RectangleShape _shape;
	// element for drawing.
	mutable Element _element;
	// matrix for saving element's states.
	Matrix _matrix;
public:
	// constructor.
	GameField(const sf::Vector2f&);
	// get position of GameField.
	sf::Vector2f get_position() const;
	// set new position.
	void set_position(const sf::Vector2f&);
	// set new matrix.
	void set_matrix(const Matrix& matrix);
	// render GameField.
	void render() const;
};

#endif

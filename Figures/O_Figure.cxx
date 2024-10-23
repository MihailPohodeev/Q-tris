#include "O_Figure.hxx"

// construct rotate positions.
void O_Figure::construct_rotate_positions()
{
	create_rotate_positions(1);
	_rotatePositions[0][0] = sf::Vector2i(0, 0);
	_rotatePositions[0][1] = sf::Vector2i(0, -1);
	_rotatePositions[0][2] = sf::Vector2i(1, -1);
	_rotatePositions[0][3] = sf::Vector2i(1, 0);
}

// constructor.
O_Figure::O_Figure() : Figure()
{
	construct_rotate_positions();
	set_position(sf::Vector2i(0, 0));
}

// copy-constructor
O_Figure::O_Figure(const O_Figure& other) : Figure(other)
{
	construct_rotate_positions();
	set_position(_position);
}

O_Figure& O_Figure::operator= (const O_Figure& other)
{
	for (U8 i = 0; i < 4; i++) 
		this->_elements[i] = other._elements[i];
	this->_position = other._position;
	this->_maxRotateIndex = other._maxRotateIndex;
	this->_currentRotateIndex = other._currentRotateIndex;
	set_position(this->_position);
	return *this;
}

// copy current figure.
O_Figure* O_Figure::clone() const
{
	return new O_Figure(*this);
}

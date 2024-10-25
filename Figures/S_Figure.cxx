#include "S_Figure.hxx"

// construct rotate positions.
void S_Figure::construct_rotate_positions()
{
	create_rotate_positions(2);
	
	_rotatePositions[0][0] = sf::Vector2i(0, 0);
	_rotatePositions[0][1] = sf::Vector2i(0, 1);
	_rotatePositions[0][2] = sf::Vector2i(-1, 1);
	_rotatePositions[0][3] = sf::Vector2i(1, 0);

	_rotatePositions[1][0] = sf::Vector2i(0, 0);
	_rotatePositions[1][1] = sf::Vector2i(-1, 0);
	_rotatePositions[1][2] = sf::Vector2i(-1, -1);
	_rotatePositions[1][3] = sf::Vector2i(0, 1);
}

// constructor.
S_Figure::S_Figure() : Figure()
{
	construct_rotate_positions();
	set_position(sf::Vector2i(0, 0));
}

// copy-constructor.
S_Figure::S_Figure(const S_Figure& other) : Figure(other)
{
	construct_rotate_positions();
	set_position(_position);
}

// operator=
S_Figure& S_Figure::operator= (const S_Figure& other)
{
	for (U8 i = 0; i < 4; i++)
		this->_elements[i] = other._elements[i];
	this->_position = other._position;
	this->_maxRotateIndex = other._maxRotateIndex;
	this->_currentRotateIndex = other._currentRotateIndex;
	set_position(this->_position);
	return *this;
}

// return copy of current I-Figure.
S_Figure* S_Figure::clone() const
{
	return new S_Figure(*this);
}


#include "O_Figure.hxx"

// constructor.
O_Figure::O_Figure() : Figure()
{
	_maxRotateIndex = 1;
	_rotatePositions = new sf::Vector2i*;
	_rotatePositions[0] = new sf::Vector2i[4];

	_rotatePositions[0][0] = sf::Vector2i(0, 0);
	_rotatePositions[0][1] = sf::Vector2i(0, -1);
	_rotatePositions[0][2] = sf::Vector2i(1, -1);
	_rotatePositions[0][3] = sf::Vector2i(1, 0);

	set_position(sf::Vector2i(0, 0));
}

// copy-constructor
O_Figure::O_Figure(const O_Figure& other) : Figure(other)
{
	_maxRotateIndex = 1;
        _rotatePositions = new sf::Vector2i*;
        _rotatePositions[0] = new sf::Vector2i[4];

        _rotatePositions[0][0] = sf::Vector2i(0, 0);
        _rotatePositions[0][1] = sf::Vector2i(0, -1);
        _rotatePositions[0][2] = sf::Vector2i(1, -1);
        _rotatePositions[0][3] = sf::Vector2i(1, 0);

	set_position(_position);
}

// operation=
O_Figure& O_Figure::operator= (O_Figure other)
{
	sf::Vector2i** t = this->_rotatePositions;
	this->_rotatePositions = other._rotatePositions;
	other._rotatePositions = t;
	
	for (U8 i = 0; i < 4; i++)
		this->_elements[i] = other._elements[i];

	this->_position 	 = other._position;
	this->_maxRotateIndex 	 = other._maxRotateIndex;
	this->_currentRotateIndex = other._currentRotateIndex;
	return *this;
}

// copy current figure.
O_Figure* O_Figure::clone() const
{
	return new O_Figure(*this);
}

#include "Figure.hxx"

// create rotate positions array.
void Figure::create_rotate_positions(U8 maxIndex)
{
	_maxRotateIndex = maxIndex;
	_rotatePositions = new sf::Vector2i*[maxIndex];
	for (U8 i = 0; i < _maxRotateIndex; i++)
		_rotatePositions[i] = new sf::Vector2i[4];
}

//--------------------------------
//-----PUBLIC-METHODS-------------
//--------------------------------
// construct.
Figure::Figure() : _currentRotateIndex(0) 
{
	set_color(sf::Color(255, 255, 255, 255));
}

// copy-constructor.
Figure::Figure(const Figure& fig)
{
	for (U8 i = 0; i < 4; i++)
		this->_elements[i] = fig._elements[i];
	this->_position = fig._position;
	this->_maxRotateIndex = fig._maxRotateIndex;
	this->_currentRotateIndex = fig._currentRotateIndex;

	_rotatePositions = new sf::Vector2i*[_maxRotateIndex];
	for (U8 i = 0; i < _maxRotateIndex; i++)
	{
		_rotatePositions[i] = new sf::Vector2i[4];
		for (U8 j = 0; j < 4; j++)
			_rotatePositions[i][j] = fig._rotatePositions[i][j];
	}
}

// set new color.
void Figure::set_color(const sf::Color& color)
{
	for (U8 i = 0; i < 4; i++)
		_elements[i].color = color;
}

sf::Color Figure::get_color() const
{
	return _elements[0].color;
}

// copy all elements to in-parameter array.
void Figure::get_all_elements(struct ElementData* destination) const
{
	for (U8 i = 0; i < 4; i++)
		destination[i] = _elements[i];
}

// move figure.
void Figure::move(const sf::Vector2i& offset)
{
	_position += offset;
	for (U8 i = 0; i < 4; i++)
		_elements[i].position += offset;
}

// set position.
void Figure::set_position(const sf::Vector2i& pos)
{
	_position = pos;
	for (U8 i = 0; i < 4; i++)
		_elements[i].position = _position + _rotatePositions[_currentRotateIndex][i];
}

// get figure's position.
sf::Vector2i Figure::get_position() const
{
	return _position;
}

// rotate figure left.
void Figure::rotate_left()
{
	_currentRotateIndex = (_maxRotateIndex + _currentRotateIndex - 1) % _maxRotateIndex;
	for (U8 i = 0; i < 4; i++)
		_elements[i].position = _position + _rotatePositions[_currentRotateIndex][i];
}

// rotate figure right.
void Figure::rotate_right()
{
	_currentRotateIndex = (_currentRotateIndex + 1) % _maxRotateIndex;
	for (U8 i = 0; i < 4; i++)
		_elements[i].position = _position + _rotatePositions[_currentRotateIndex][i];
}

// destructor.
Figure::~Figure()
{
	for( U8 i = 0; i < _maxRotateIndex; i++ )
		delete _rotatePositions[i];
	delete _rotatePositions;
}

#include "Matrix.hxx"

// constructor of matrix
Matrix::Matrix()
{
	// create buffer and fill it nullptrs.
	_buffer = new struct ElementData** [10];
	for (int i = 0; i < 10; i++)
	{
		_buffer[i] = new struct ElementData* [20];
		for (int j = 0; j < 20; j++)
			_buffer[i][j] = nullptr;
	}
}

// add new element in matrix.
void Matrix::add_element(const struct ElementData& elem)
{
	sf::Vector2i pos = elem.position;
	if (!_buffer[pos.x][pos.y])
	{
		_buffer[pos.x][pos.y] = new struct ElementData;
	}
	*(_buffer[pos.x][pos.y]) = elem;
}

// copy current Matrix.
Matrix* Matrix::clone() const
{
	Matrix* result = new Matrix;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 20; j++)
			if (this->_buffer[i][j])
				result->_buffer[i][j] = this->_buffer[i][j]->clone();
	return result;
}

// destructor.
Matrix::~Matrix()
{
	// clear all memory.
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
			if (_buffer[i][j])
				delete _buffer[i][j];
		delete _buffer[i];
	}
	delete _buffer;
}

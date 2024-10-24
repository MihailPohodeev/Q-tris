#include "Matrix.hxx"

// constructor of matrix.
Matrix::Matrix()
{
	// create buffer and fill it nullptrs.
	_buffer = new struct ElementData** [10];
	for (U8 i = 0; i < 10; i++)
	{
		_buffer[i] = new struct ElementData* [20];
		for (U8 j = 0; j < 20; j++)
			_buffer[i][j] = nullptr;
	}
}

// copy-constructor.
Matrix::Matrix(const Matrix& other)
{
	_buffer = new struct ElementData** [10];
	for (U8 i = 0; i < 10; i++)
	{
		_buffer[i] = new struct ElementData* [20];
		for (U8 j = 0; j < 20; j++)
		{
			if (other._buffer[i][j])
				this->_buffer[i][j] = other._buffer[i][j]->clone();
			else
				this->_buffer[i][j] = nullptr;
		}
	}
}

// add new figure into the Matrix.
void Matrix::add_figure(const Figure& figure)
{
	struct ElementData elems[4];
	figure.get_all_elements(elems);
	for (U8 i = 0; i < 4; i++)
		this->add_element(elems[i]);
}

// add new element in matrix.
void Matrix::add_element(const struct ElementData& elem)
{
	sf::Vector2i pos = elem.position;
	if (pos.x >= 0 && pos.x < 10 && pos.y >= 0 && pos.y < 20)
	{
		if (!_buffer[pos.x][pos.y])
		{
			_buffer[pos.x][pos.y] = new struct ElementData;
		}
		*(_buffer[pos.x][pos.y]) = elem;
	}
}

// return buffer's address.
struct ElementData*** Matrix::get_buffer() const
{
	return _buffer;
}

// operator=.
Matrix& Matrix::operator= (Matrix other)
{
	struct ElementData*** t = this->_buffer;
	this->_buffer = other._buffer;
	other._buffer = t;
	return *this;
}

// copy current Matrix.
Matrix* Matrix::clone() const
{
	return new Matrix(*this);
}

// destructor.
Matrix::~Matrix()
{
	// clear all memory.
	for (U8 i = 0; i < 10; i++)
	{
		for (U8 j = 0; j < 20; j++)
			if (_buffer[i][j])
			{
				delete _buffer[i][j];
			}
		delete _buffer[i];
	}
	delete _buffer;
}

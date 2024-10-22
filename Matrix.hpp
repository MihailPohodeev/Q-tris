#ifndef _MATRIX_H_
#define _MATRIX_H_

/*
 * 	Matrix for saving information about elements and current figure.
 * 	Informaions sends to Server and received from server.
 * 	Double Bufferezation:
 *
 * 	BUFFER_1:
 * 	 _   _
 * 	| ... |
 * 	| ... | <- write new state of field here.
 * 	| ... |
 * 	|_   _|
 *
 * 	BUFFER_2:
 * 	 _   _
 * 	| ... |
 * 	| ... | -> send info to Server from another buffer
 * 	| ... |
 * 	|_   _|
 */

#include <mutex>
#include "Element.hxx"

class Matrix
{
	struct ElementData*** _buffer;

public:
	// constructor
	Matrix()
	{
		// create two buffers.
		_buffer = new struct ElementData** [10];
		for (int i = 0; i < 10; i++)
		{
			_buffer[i] = new struct ElementData* [20];
			for (int j = 0; j < 20; j++)
				_buffer[i][j] = nullptr;
		}
	}

	struct ElementData*** get_matrix() const
	{
		struct ElementData*** newData = new struct ElementData** [10];
	}

	void add_element(const struct ElementData& elem)
	{
		sf::Vector2i pos = elem.position;
		if (!_buffer[pos.x][pos.y])
		{
			_buffer[pos.x][pos.y] = new struct ElementData;
		}
		*(_buffer[pos.x][pos.y]) = elem;
	}

	// destructor.
	~Matrix()
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
}

class DoubleFrame
{
	Matrix* _workingMatrix;
	Matrix* _readyMatrix;
public:
	DoubleFrame()
	{
		_workingMatrix	= new Matrix;
		_readyMatrix	= new Matrix;
	}

	~DoubleFrame()
	{
		delete _workingMatrix;
		delete _readyMatrix;
	}
};

#endif

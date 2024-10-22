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
	// constructor.
	Matrix();
	// add new element in Matrix.
	void add_element(const struct ElementData&);
	// copy current Matrix.
	Matrix* clone() const;
	// destructor.
	~Matrix();
};

#endif

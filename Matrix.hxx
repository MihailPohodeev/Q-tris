#ifndef _MATRIX_HXX_
#define _MATRIX_HXX_

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
#include "setup.hxx"
#include "Figures/Element.hxx"
#include "Figures/Figure.hxx"

class Matrix
{
	struct ElementData*** _buffer;
public:
	// constructor.
	Matrix();
	// copy-constructor.
	Matrix(const Matrix&);
	// add figure in Matrix.
	void add_figure(const Figure&);
	// add new element in Matrix.
	void add_element(const struct ElementData&);
	// ! return buffers addr ! DANGEROUS
	struct ElementData*** get_buffer() const;
	// operator=
	Matrix& operator= (Matrix);
	// copy current Matrix.
	Matrix* clone() const;
	// destructor.
	~Matrix();
};

#endif

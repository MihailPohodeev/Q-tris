#ifndef _O_FIGURE_H_
#define _O_FIGURE_H_

#include "Figure.hxx"

class O_Figure : public Figure
{
public:
	// constructor.
	O_Figure();
	// copy-constructor.
	O_Figure(const O_Figure&);
	// operator=
	O_Figure& operator= (O_Figure);
	// rotate right.
	void rotate_right();
	// rotate left.
	void rotate_left();
	// copy current figure.
	O_Figure* clone() const override;
};

#endif

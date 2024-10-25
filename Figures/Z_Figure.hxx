#ifndef _Z_FIGURE_H_
#define _Z_FIGURE_H_

#include "Figure.hxx"

class Z_Figure : public Figure
{
	// construct rotate positions
	void construct_rotate_positions() override;
public:
	// constructor.
	Z_Figure();
	// copy-constructor.
	Z_Figure(const Z_Figure&);
	// operator=
	Z_Figure& operator= (const Z_Figure&);
	// copy current figure.
	Z_Figure* clone() const override;
};

#endif

#ifndef _O_FIGURE_H_
#define _O_FIGURE_H_

#include "Figure.hxx"

class O_Figure : public Figure
{
	// construct rotate positions.
	void construct_rotate_positions() override;
public:
	// constructor.
	O_Figure();
	// copy-constructor.
	O_Figure(const O_Figure&);
	// operator=
	O_Figure& operator= (const O_Figure&);
	// copy current figure.
	O_Figure* clone() const override;
};

#endif

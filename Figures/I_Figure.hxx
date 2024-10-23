#ifndef _I_FIGURE_H_
#define _I_FIGURE_H_

#include "Figure.hxx"

class I_Figure : public Figure
{
	// construct rotate positions
	void construct_rotate_positions() override;
public:
	// constructor.
	I_Figure();
	// copy-constructor.
	I_Figure(const I_Figure&);
	// operator=
	I_Figure& operator= (const I_Figure&);
	// copy current figure.
	I_Figure* clone() const override;
};

#endif

#ifndef _L_FIGURE_H_
#define _L_FIGURE_H_

#include "Figure.hxx"

class L_Figure : public Figure
{
	// construct rotate positions
	void construct_rotate_positions() override;
public:
	// constructor.
	L_Figure();
	// copy-constructor.
	L_Figure(const L_Figure&);
	// operator=
	L_Figure& operator= (const L_Figure&);
	// copy current figure.
	L_Figure* clone() const override;
};

#endif

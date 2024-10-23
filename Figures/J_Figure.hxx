#ifndef _J_FIGURE_H_
#define _J_FIGURE_H_

#include "Figure.hxx"

class J_Figure : public Figure
{
	// construct rotate positions
	void construct_rotate_positions() override;
public:
	// constructor.
	J_Figure();
	// copy-constructor.
	J_Figure(const J_Figure&);
	// operator=
	J_Figure& operator= (const J_Figure&);
	// copy current figure.
	J_Figure* clone() const override;
};

#endif

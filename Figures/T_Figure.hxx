#ifndef _T_FIGURE_H_
#define _T_FIGURE_H_

#include "Figure.hxx"

class T_Figure : public Figure
{
	// construct rotate positions
	void construct_rotate_positions() override;
public:
	// constructor.
	T_Figure();
	// copy-constructor.
	T_Figure(const T_Figure&);
	// operator=
	T_Figure& operator= (const T_Figure&);
	// copy current figure.
	T_Figure* clone() const override;
};

#endif

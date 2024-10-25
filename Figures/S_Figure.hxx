#ifndef _S_FIGURE_HXX_
#define _S_FIGURE_HXX_

#include "Figure.hxx"

class S_Figure : public Figure
{
	// construct rotate positions
	void construct_rotate_positions() override;
public:
	// constructor.
	S_Figure();
	// copy-constructor.
	S_Figure(const S_Figure&);
	// operator=
	S_Figure& operator= (const S_Figure&);
	// copy current figure.
	S_Figure* clone() const override;
};

#endif

#ifndef _FIGURE_O_H_
#define _FIGURE_O_H_

#include "Figure.hxx"

class FigureO : public Figure
{

public:
    FigureO(float, float);
    FigureO(const sf::Vector2f&);
};

#endif
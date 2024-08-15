#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "setup.hxx"
#include "Figures/FigureL.hxx"
#include "Figures/FigureO.hxx"
#include "Matrix.hxx"

class Window
{
    Matrix* matrix;
    Figure* currentFigure;
    sf::Vector2f size;

    sf::Vector2f figureSpawnPosition;
    sf::Vector2f center;
    sf::Clock clock;

public:
    Window(float, float);
    Window(const sf::Vector2f&);
    ~Window();

    void set_center(const sf::Vector2f&);

    void update();
    void render() const;
};

#endif
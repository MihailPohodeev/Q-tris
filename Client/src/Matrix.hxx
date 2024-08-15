#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "setup.hxx"
#include "Figures/Element.hxx"
#include "Figures/Figure.hxx"

class Matrix
{
    Element*** matrix;

    sf::Vector2f size;
    sf::RectangleShape background;

public:

    Matrix(float, float);
    Matrix(const sf::Vector2f&);
    Matrix(const Matrix& mat);
    ~Matrix();
    Matrix operator=(const Matrix&);

    void set_position(const sf::Vector2f&);
    
    bool connect_figure(Figure*);

    void render() const;

};

#endif
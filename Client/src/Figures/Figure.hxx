#ifndef _FIGURE_H_
#define _FIGURE_H_

#include "../setup.hxx"
#include "Element.hxx"

class Figure
{
    sf::Vector2f position;
    sf::Vector2i matrixPosition;

protected:
    Element elements[4];
    U8 currentRotationIndex;
    U8 countOfRotationIndexes;
    sf::Vector2i* rotationPositions;

public:

    Figure(float, float);
    Figure(const sf::Vector2f&);
    Figure(const Figure&);
    Figure operator= (const Figure&);

    void set_position(const sf::Vector2f&);
    sf::Vector2f get_position() const;
    void move(const sf::Vector2f&);
    void set_matrix_position(const sf::Vector2i&);
    sf::Vector2i get_matrix_position() const;
    void matrix_move(const sf::Vector2i&);

    // rotate figure.
    void rotate_right();
    //virtual void rotate_left();

    // set rotate index.
    void set_rotation_index(U8);

    // get elements array.
    Element* get_elements();

    void render() const;

};

#endif
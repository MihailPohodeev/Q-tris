#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "../setup.hxx"

class Element
{
    sf::RectangleShape shape;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Vector2i matrixPosition;
    sf::Color color;

public:

    Element(float, float);
    Element(const sf::Vector2f&);
    //~Element();

    // translation methods
    void set_position(const sf::Vector2f&);
    sf::Vector2f get_position() const;
    void move(const sf::Vector2f&);

    void set_matrix_position(const sf::Vector2i&);
    sf::Vector2i get_matrix_position() const;
    void matrix_move(const sf::Vector2i&);

    // size
    sf::Vector2f get_size() const;

    // color
    void set_color(const sf::Color&);
    sf::Color get_color() const;

    void render() const;      // render element.

};

#endif
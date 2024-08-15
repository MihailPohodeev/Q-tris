#include "Element.hxx"

extern sf::RenderWindow* window;

Element::Element(float width, float height) : shape(sf::Vector2f(width, height))
{
    color           = sf::Color(255, 255, 255, 255);
    size            = sf::Vector2f(width, height);
    position        = sf::Vector2f(0.0, 0.0);
    matrixPosition  = sf::Vector2i(0, 0);

    //shape.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
}

Element::Element(const sf::Vector2f& size) : shape(sf::Vector2f(size.x, size.y))
{
    *this = Element(size.x, size.y);
}

void Element::set_position(const sf::Vector2f& pos)
{
    position = pos;
    shape.setPosition(pos);
}

sf::Vector2f Element::get_position() const
{
    return position;
}

void Element::move(const sf::Vector2f& inc)
{
    position += inc;
    shape.move(inc);
}

void Element::set_matrix_position(const sf::Vector2i& pos)
{
    matrixPosition = pos;
    set_position(sf::Vector2f(position.x + size.x * pos.x, position.y + size.y * pos.y));
}

sf::Vector2i Element::get_matrix_position() const
{
    return matrixPosition;
}

void Element::matrix_move(const sf::Vector2i& inc)
{
    matrixPosition += inc;
    move(sf::Vector2f(size.x * inc.x, size.y * inc.y));
}

sf::Vector2f Element::get_size() const
{
    return size;
}

void Element::set_color(const sf::Color& col)
{
    color = col;
    shape.setFillColor(col);
}

sf::Color Element::get_color() const
{
    return color;
}

void Element::render() const
{
    window->draw(shape);
}
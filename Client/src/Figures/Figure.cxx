#include "Figure.hxx"

extern sf::RenderWindow* window;

Figure::Figure(float elemWidth, float elemHeight) : elements{   Element(elemWidth, elemHeight),
                                                                Element(elemWidth, elemHeight),
                                                                Element(elemWidth, elemHeight),
                                                                Element(elemWidth, elemHeight)}
{
    position = sf::Vector2f(0.0, 0.0);
    matrixPosition = sf::Vector2i(0, 0);
}

Figure::Figure(const sf::Vector2f& sz) : elements{   Element(sz.x, sz.y),
                                                     Element(sz.x, sz.y),
                                                     Element(sz.x, sz.y),
                                                     Element(sz.x, sz.y)}
{
    *this = Figure(sz.x, sz.y);
}

Figure::Figure(const Figure& other) : elements { other.elements[0], other.elements[1], other.elements[2], other.elements[3] }
{
    for (U8 i = 0; i < 3 * countOfRotationIndexes; i++)
        this->rotationPositions[i] = other.rotationPositions[i];
}

Figure Figure::operator=(const Figure& other)
{
    return Figure(other);
}

void Figure::set_position(const sf::Vector2f& pos)
{
    position = pos;
    sf::Vector2f difference;
    difference = elements[1].get_position() - elements[0].get_position();
    elements[1].set_position(pos + difference);
    difference = elements[2].get_position() - elements[0].get_position();
    elements[2].set_position(pos + difference);
    difference = elements[3].get_position() - elements[0].get_position();
    elements[3].set_position(pos + difference);
    elements[0].set_position(pos);
}

sf::Vector2f Figure::get_position() const
{
    return position;
}

void Figure::move(const sf::Vector2f& inc)
{
    set_position(position + inc);
}

void Figure::set_matrix_position(const sf::Vector2i& pos)
{
    sf::Vector2i diff = pos - matrixPosition;
    matrixPosition = pos;
    sf::Vector2f elemSize = elements[0].get_size();
    move(sf::Vector2f(elemSize.x * diff.x, elemSize.y * diff.y));
}

sf::Vector2i Figure::get_matrix_position() const
{
    return matrixPosition;
}

void Figure::matrix_move(const sf::Vector2i& inc)
{
    set_matrix_position(matrixPosition + inc);
}

void Figure::rotate_right()
{   
    if ( (++currentRotationIndex) >= countOfRotationIndexes )
        currentRotationIndex = 0;

    set_rotation_index(currentRotationIndex);
}

void Figure::set_rotation_index(U8 index)
{
    for (U8 i = 1; i < 4; i++)
        elements[i].set_position(elements[0].get_position());
    elements[1].matrix_move(rotationPositions[index * 3]);
    elements[2].matrix_move(rotationPositions[index * 3 + 1]);
    elements[3].matrix_move(rotationPositions[index * 3 + 2]);
}

Element* Figure::get_elements()
{
    return elements;
}

void Figure::render() const
{
    for (U8 i = 0; i < 4; i++)
        elements[i].render();
}
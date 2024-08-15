#include "FigureO.hxx"

FigureO::FigureO(float elemWidth, float elemHeight) : Figure(elemWidth, elemHeight)
{
    currentRotationIndex   = 0;
    countOfRotationIndexes = 1;

    rotationPositions = new sf::Vector2i[countOfRotationIndexes * 3];
    
    rotationPositions[0] = sf::Vector2i(1, 0);
    rotationPositions[1] = sf::Vector2i(0, -1);
    rotationPositions[2] = sf::Vector2i(1, -1);

    set_rotation_index(currentRotationIndex);
}

FigureO::FigureO(const sf::Vector2f& elemSize) : Figure(elemSize.x, elemSize.y)
{
    *this = FigureO(elemSize.x, elemSize.y);
}
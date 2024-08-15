#include "FigureL.hxx"

FigureL::FigureL(float elemWidht, float elemHeight) : Figure(elemWidht, elemHeight)
{
    currentRotationIndex   = 0;
    countOfRotationIndexes = 4;
    
    rotationPositions = new sf::Vector2i[countOfRotationIndexes * 3];

    rotationPositions[0] = sf::Vector2i(1, 0);
    rotationPositions[1] = sf::Vector2i(0, -1);
    rotationPositions[2] = sf::Vector2i(0, -2);

    rotationPositions[3] = sf::Vector2i(0, 1);
    rotationPositions[4] = sf::Vector2i(1, 0);
    rotationPositions[5] = sf::Vector2i(2, 0);

    rotationPositions[6] = sf::Vector2i(-1, 0);
    rotationPositions[7] = sf::Vector2i(0, 1);
    rotationPositions[8] = sf::Vector2i(0, 2);

    rotationPositions[9]  = sf::Vector2i(0, -1);
    rotationPositions[10] = sf::Vector2i(-1, 0);
    rotationPositions[11] = sf::Vector2i(-2, 0);

    set_rotation_index(currentRotationIndex);
}

FigureL::FigureL(const sf::Vector2f& elemSize) : Figure(elemSize)
{
    *this = FigureL(elemSize.x, elemSize.y);
}
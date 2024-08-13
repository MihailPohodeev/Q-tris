#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <vector>

#include "Element.hxx"
#include "../setup.hxx"

class Figure
{
protected:
    Element _elementsArray[4];
    glm::vec2 _position;
    U32 _currentRotationIndex;
    U32 _amountOfRotationIndex;
public:
    Figure();
    ~Figure();

    void move(const glm::vec2&);
    virtual void rotate_right() = 0;
    virtual void rotare_left() = 0;
    std::vector<Element*> get_elements_array(std::vector<Element*>&);
    void render();
};

#endif
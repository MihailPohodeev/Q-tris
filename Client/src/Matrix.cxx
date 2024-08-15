#include "Matrix.hxx"

extern sf::RenderWindow* window;

Matrix::Matrix(float width, float height) : background(sf::Vector2f(width, height)), size(width, height)
{
    background.setFillColor(sf::Color(128, 128, 128, 255));
    matrix = new Element**[20];
    for (U8 i = 0; i < 20; i++)
    {
        matrix[i] = new Element*[10];
        for (U8 j = 0; j < 10; j++)
            matrix[i][j] = nullptr;
    }
}

Matrix::Matrix(const sf::Vector2f& sz) : background(sz), size(sz)
{
    *this = Matrix(size.x, size.y);
}

Matrix::Matrix(const Matrix& other)
{
    for (U8 i = 0; i < 20; i++)
        for (U8 j = 0; j < 10; j++)
        {
            if(other.matrix[i][j])
            {
                this->matrix[i][j] = new Element(*other.matrix[i][j]);
            }
        }
}

// destructor deallocation memory.
Matrix::~Matrix()
{
    for (U8 i = 0; i < 20; i++)
    {
        for (U8 j = 0; j < 10; j++)
        {
            if (matrix[i][j])
                delete matrix[i][j];
        }
        delete matrix[i];
    }
    delete matrix;
}

Matrix Matrix::operator=(const Matrix& other)
{
    return Matrix(other);
}

void Matrix::set_position(const sf::Vector2f& pos)
{
    background.setPosition(pos);
    for (U8 i = 0; i < 20; i++)
        for (U8 j = 0; j < 10; j++)
        {
            if (matrix[i][j])
            {
                matrix[i][j]->set_matrix_position(sf::Vector2i(0, 0));
                matrix[i][j]->set_position(pos);
                matrix[i][j]->matrix_move(sf::Vector2i(j, i));
            }
        }
}

bool Matrix::connect_figure(Figure* fig)
{
    Element* elemArray = fig->get_elements();
    for (U8 i = 0; i < 4; i++)
    {
        sf::Vector2i elemPos = elemArray[i].get_matrix_position();
        if(elemPos.y >= 19)
            return true;
    }
    return false;
}

void Matrix::render() const
{
    window->draw(background);
    for (U8 i = 0; i < 20; i++)
        for (U8 j = 0; j < 10; j++)
            if (matrix[i][j])
                matrix[i][j]->render();
}
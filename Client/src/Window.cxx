#include "Window.hxx"

Window::Window(float width, float height) : size(width, height)
{
    matrix = new Matrix(width / 2, height);
    currentFigure = new FigureL(size.x / 20, size.y / 20);
}

void Window::set_center(const sf::Vector2f& pos)
{
    center = pos;
    figureSpawnPosition = sf::Vector2f(pos.x - size.x / 4, pos.y - size.y / 2);
    currentFigure->set_matrix_position(sf::Vector2i(5, 1));
    currentFigure->set_position(figureSpawnPosition);
    matrix->set_position(sf::Vector2f(pos.x - size.x / 2, pos.y - size.y / 2));
}

void Window::update()
{
    if ((float)clock.getElapsedTime().asMilliseconds() > 1'000)
    {
        if (matrix->connect_figure(currentFigure))
        {
            currentFigure = new FigureO(size.x / 20, size.y / 20);
            currentFigure->set_position(figureSpawnPosition);
        }

        currentFigure->matrix_move(sf::Vector2i(0, 1));
        std::cout << currentFigure->get_matrix_position().x << ' ' << currentFigure->get_matrix_position().y << '\n';
        clock.restart();
    }
}

void Window::render() const
{
    matrix->render();
    currentFigure->render();
}

Window::~Window()
{
    delete matrix;
    delete currentFigure;
}
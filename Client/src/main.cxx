#include <iostream>
#include "setup.hxx"
#include "Window.hxx"

U32 SCR_WIDTH  = 800;
U32 SCR_HEIGHT = 600;

sf::RenderWindow* window;

int main(int argc, char** argv)
{
    window = new sf::RenderWindow(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Q-tris!");

    //Element elem(sf::Vector2f(50, 50));
    //elem.matrix_move(sf::Vector2i(1, 1));
    //elem.set_color(sf::Color(79, 230, 178, 255));

    Window win(500, 500);
    win.set_center(sf::Vector2f(SCR_WIDTH / 2, SCR_HEIGHT / 2));

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        win.update();
        window->clear();
        win.render();
        window->display();
    }

    return 0;
}
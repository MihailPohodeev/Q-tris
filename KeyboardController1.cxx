#include <SFML/Graphics.hpp>
#include "KeyboardController1.hxx"


// rotate right the figure.
bool KeyboardController1::is_rotate_right()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		return true;
	return false;
}

// rotate left the figure.
bool KeyboardController1::is_rotate_left()
{
	return false;
}

// move right the figure
bool KeyboardController1::is_move_right()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		return true;
	return false;
}

// move left the figure.
bool KeyboardController1::is_move_left()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return true;
	return false;
}

// drow figure.
bool KeyboardController1::is_drop()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		return true;
	return false;
}

// accelerate figure.
bool KeyboardController1::is_accelerate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		return true;
	return false;
}

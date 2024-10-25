#include <SFML/Graphics.hpp>
#include "KeyboardController1.hxx"

// contructor;
KeyboardController1::KeyboardController1() : Controller() {}

// rotate right the figure.
bool KeyboardController1::is_rotate_right()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!_isRotateRight)
		{
			_isRotateRight = true;
			return true;
		}
	}
	else _isRotateRight = false;
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
	{
		if (!_isMoveRight)
		{
			_isMoveRight = true;
			return true;
		}
	}
	else _isMoveRight = false;
	return false;
}

// move left the figure.
bool KeyboardController1::is_move_left()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!_isMoveLeft)
		{
			_isMoveLeft = true;
			return true;
		}
	}
	else _isMoveLeft = false;
	return false;
}

// drow figure.
bool KeyboardController1::is_drop()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!_isDrop)
		{
			_isDrop = true;
			return true;
		}
	}
	else _isDrop = false;
	return false;
}

// accelerate figure.
bool KeyboardController1::is_accelerate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		return true;
	return false;
}

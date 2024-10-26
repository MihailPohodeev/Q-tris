#include <SFML/Graphics.hpp>
#include "JoystickController.hxx"

// constructor.
JoystickController::JoystickController(U32 desc) : _joystickDescriptor(desc), _deltaTime(125) {}

// rotate right the figure.
bool JoystickController::is_rotate_right()
{
	if (sf::Joystick::isButtonPressed(_joystickDescriptor, 0))
	{
		if (!_isRotateRight)
		{
			_isRotateRight = true;
			return true;
		}
	}
	else
		_isRotateRight = false;
	return false;
}

// rotate left the figure.
bool JoystickController::is_rotate_left()
{
	if (sf::Joystick::isButtonPressed(_joystickDescriptor, 3))
		return true;
	return false;
}

// move right the figure
bool JoystickController::is_move_right()
{
	float x = sf::Joystick::getAxisPosition(_joystickDescriptor, sf::Joystick::X);
	x /= 100.f;
	if (x > 0.5f)
	{
		if (_clock.getElapsedTime().asMilliseconds() > _deltaTime)
		{
			_clock.restart();
			return true;
		}
	}
	return false;
}

// move left the figure.
bool JoystickController::is_move_left()
{
	float x = sf::Joystick::getAxisPosition(_joystickDescriptor, sf::Joystick::X);
	x /= 100.f;
	if (x < -0.5f)
	{
		if (_clock.getElapsedTime().asMilliseconds() > _deltaTime)
		{
			_clock.restart();
			return true;
		}
	}
	else
		_isMoveLeft = false;
	return false;
}

// drow figure.
bool JoystickController::is_drop()
{
        if (sf::Joystick::isButtonPressed(_joystickDescriptor, 2))
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
bool JoystickController::is_accelerate()
{
	float y = sf::Joystick::getAxisPosition(_joystickDescriptor, sf::Joystick::Y);
	y /= 100.f;
        if (y > 0.5f)
                return true;
        return false;
}


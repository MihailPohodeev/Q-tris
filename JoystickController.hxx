#ifndef _JOYSTICK_CONTROLLER_H_
#define _JOYSTICK_CONTROLLER_H_

#include <SFML/Graphics.hpp>
#include "setup.hxx"
#include "Controller.hxx"

class JoystickController : public Controller
{
	sf::Clock _clock;
	U32 _joystickDescriptor;
	U32 _deltaTime;
public:
	JoystickController(U32);
	bool is_rotate_right()  override;
	bool is_rotate_left()   override;
	bool is_move_right()    override;
	bool is_move_left()     override;
	bool is_drop()          override;
	bool is_accelerate()    override;
};

#endif

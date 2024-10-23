#ifndef _JOYSTICK_CONTROLLER_H_
#define _JOYSTICK_CONTROLLER_H_

#include "setup.hxx"
#include "Controller.hxx"

class JoystickController : public Controller
{
	U32 _joystickDescriptor;
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

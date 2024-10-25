#ifndef _KEYBOARD_CONTROLLER_1_H_
#define _KEYBOARD_CONTROLLER_1_H_

#include "Controller.hxx"

class KeyboardController1 : public Controller
{
public:
	KeyboardController1();
	bool is_rotate_right()	override;
	bool is_rotate_left()	override;
	bool is_move_right()	override;
	bool is_move_left()	override;
	bool is_drop()		override;
	bool is_accelerate()	override;
};

#endif

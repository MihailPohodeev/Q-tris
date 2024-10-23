#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

class Controller
{
public:
	virtual bool is_rotate_right() = 0;
	virtual bool is_rotate_left() = 0;
	virtual bool is_move_right() = 0;
	virtual bool is_move_left() = 0;
	virtual bool is_drop() = 0;
	virtual bool is_accelerate() = 0;
};

#endif

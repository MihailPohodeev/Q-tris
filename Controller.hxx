#ifndef _CONTROLLER_HXX_
#define _CONTROLLER_HXX_

class Controller
{
protected:
	bool _isRotateRight, _isRotateLeft, _isMoveRight, _isMoveLeft, _isDrop;
public:
	Controller() : _isRotateRight(false), _isRotateLeft(false), _isMoveRight(false), _isMoveLeft(false), _isDrop(false) {}
	virtual bool is_rotate_right() = 0;
	virtual bool is_rotate_left() = 0;
	virtual bool is_move_right() = 0;
	virtual bool is_move_left() = 0;
	virtual bool is_drop() = 0;
	virtual bool is_accelerate() = 0;
};

#endif

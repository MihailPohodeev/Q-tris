#ifndef _REAL_PLAYER_HXX_
#define _REAL_PLAYER_HXX_

#include <queue>
#include "Matrix.hxx"
#include "DoubleFrame.hxx"
#include "PlayerObject.hxx"
#include "Controller.hxx"

class RealPlayer : public PlayerObject
{
	// boolean variables for pressing buttons.
	bool isMoveRight, isMoveLeft, isRotateLeft, isRotateRight, isDrop, isAccelerate;
	// clock for managing speed of game.
	sf::Clock _clock;
	// controller for managing.
	Controller* _controller;
	// queue for getting the same figures by clients.
	std::queue<U8> _figuresIndecesQueue;
	// current figure.
	Figure* _currentFigure;
	// matrix where the game is happens.
	Matrix _matrixForWork;

	// get new _currentFigure.
	void _update_the_figure();
	// get new figures.
	void _get_new_figures_to_queue();
public:
	// constructor.
	RealPlayer();
	// set controller.
	void set_controller(Controller*);
	// update data.
	void update() override;
	// exchange data with server.
	void exchange_data() override;
};

#endif

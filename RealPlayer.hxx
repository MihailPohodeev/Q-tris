#ifndef _REAL_PLAYER_HXX_
#define _REAL_PLAYER_HXX_

#include <queue>
#include <vector>
#include <mutex>

#include "Matrix.hxx"
#include "DoubleFrame.hxx"
#include "PlayerObject.hxx"
#include "Controller.hxx"

class RealPlayer : public PlayerObject
{
	float _speed;
	// current state for level increment.
	U16 _currentLevelIncrementState;
	// count of lines, that nesessary for level update
	U16 _incrementForLevel;
	// clock for managing speed of game.
	sf::Clock _clock;
	// clock for exchanging data with Server.
	sf::Clock _clockForDataSending;
	// clock for receiving figures.
	sf::Clock _clockReceivingFigures;
	// controller for managing.
	Controller* _controller;
	// queue for getting the same figures by clients.
	std::queue<U8> _figuresIndecesQueue;
	// current figure.
	Figure* _currentFigure;
	// matrix where the game is happens.
	Matrix _matrixForWork;
	// mutex for _figuresIndecesQueue guard.
	mutable std::mutex _figuresIndecesQueueGuard;

	// get new _currentFigure.
	void _update_the_figure();
	// get new figures.
	void _get_new_figures_to_queue();
public:
	// constructor.
	RealPlayer();
	// destructor.
	virtual ~RealPlayer() {}
	// set controller.
	void set_controller(Controller*);
	// update data.
	void update() override;
	// exchange data with server.
	void exchange_data() override;
	// get next index of figure.
	U8 get_next_figure_index() override;
	// set new figures.
	void set_new_figures(const std::vector<U8>&);
};

#endif

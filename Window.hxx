#ifndef _WINDOW_HXX_
#define _WINDOW_HXX_

#include "PlayerObject.hxx"
#include "GameField.hxx"
#include "ScoreTable.hxx"
#include "DoubleFrame.hxx"

class Window
{
	PlayerObject* _player;
	GameField _gameField;
	ScoreTable _scoreTable;
	DoubleFrame _doubleFrame;

	sf::Vector2f _size;
public:
	// constructor.
	Window(const sf::Vector2f&);
	// set player object.
	void set_player_object(PlayerObject* player);
	// set new position.
	void set_position(const sf::Vector2f&);
	// set new position
	// update data.
	void update();
	// render.
	void render() const;
};

#endif

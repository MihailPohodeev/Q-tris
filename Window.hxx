#ifndef _WINDOW_HXX_
#define _WINDOW_HXX_

#include <string>

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

	// notification of game over.
	sf::RectangleShape _notification;
	sf::Text _gameOverHeader;

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
	// set username.
	void set_username(const std::string&);
};

#endif

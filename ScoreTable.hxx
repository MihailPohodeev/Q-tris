#ifndef _SCORE_TABLE_H_
#define _SCORE_TABLE_H_

#include <SFML/Graphics.hpp>
#include "setup.hxx"

class ScoreTable
{
	sf::RectangleShape _shape;
	sf::Text _scoreHeader;
	sf::Text _linesHeader;
	sf::Text _levelHeader;
	U64 _score;
	U32 _lines;
	U32 _level;
public:
	// constructor.
	ScoreTable(const sf::Vector2f&);
	// set size of Score Table.
	void set_size(const sf::Vector2f&);
	// get size of Score Table.
	sf::Vector2f get_size() const;
	// set new position.
	void set_position(const sf::Vector2f&);
	// get current position.
	sf::Vector2f get_position() const;
	// set and get Score.
	void set_score(U64);
	U64 get_score() const;
	// set and get destroyed lines.
	void set_lines(U32);
	U32 get_lines() const;
	// set and get level.
	void set_level(U32);
	U32 get_level() const;
	// render.
	void render() const;
};

#endif

#ifndef _PLAYER_OBJECT_HXX_
#define _PLAYER_OBJECT_HXX_

#include "setup.hxx"
#include "GameField.hxx"
#include "ScoreTable.hxx"
#include "DoubleFrame.hxx"

class PlayerObject
{
protected:
	U64 _score;
	U32 _lines;
	U32 _level;
	bool _isGameOver;

	DoubleFrame* _doubleFrame;
public:
	PlayerObject() : _score(0), _lines(0), _level(0), _isGameOver(false), _doubleFrame(nullptr) {}
	virtual ~PlayerObject() {};
	virtual void update() = 0;
	virtual void exchange_data() = 0;
	virtual void set_double_frame(DoubleFrame* df) { _doubleFrame = df; }
	virtual bool is_game_over() const { return _isGameOver; }
	virtual U64 get_score() const { return _score; }
	virtual U32 get_lines() const { return _lines; }
	virtual U32 get_level() const { return _level; }
};

#endif

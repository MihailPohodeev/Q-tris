#ifndef _PLAYER_OBJECT_H_
#define _PLAYER_OBJECT_H_

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

	DoubleFrame* _doubleFrame;
public:
	PlayerObject() : _score(0), _lines(0), _level(1) {}
	virtual void update() = 0;
	virtual void exchange_data() = 0;
	virtual void set_double_frame(DoubleFrame* df) { _doubleFrame = df; }
	virtual U64 get_score() const { return _score; }
	virtual U32 get_lines() const { return _lines; }
	virtual U32 get_level() const { return _level; }
};

#endif

#ifndef _PLAYER_OBJECT_H_
#define _PLAYER_OBJECT_H_

#include "GameField.hxx"
#include "ScoreTable.hxx"

class PlayerObject
{
public:
	virtual void set_game_field(GameField*) = 0;
	virtual void set_score_table(ScoreTable*) = 0;
	virtual void update() = 0;
	virtual void exchange_data() = 0;
};

#endif

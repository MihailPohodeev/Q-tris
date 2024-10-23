#ifndef _REAL_PLAYER_H_
#define _REAL_PLAYER_H_

#include "ScoreTable.hxx"
#include "GameField.hxx"

class RealPlayer : public PlayerObject
{
	GameField* _gameField;
	ScoreTable* _scoreTable;
public:
	void set_game_field(GameField*) override;
	void set_score_table(ScoreTable*) override;
};

#endif

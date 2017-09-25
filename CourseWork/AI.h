#pragma once
#include "Player.h"
enum situation{ bad, normal, good, nice };
class bot : public player
{
public:
	bot(char* name) : player(name)
	{
	}
	void rethrow_dices();
	//ситуация с костями бота
	int get_situation();
	//бот делает ставку основываясь на ситуации с костями
	int make_bet();
	friend ostream& operator <<(ostream& out, bot& pl);
};

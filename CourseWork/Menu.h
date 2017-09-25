#pragma once
#include "ai.h"
class menu
{
public:
	int bank = 0;
	int bet1;
	int bet2;
	int ask_bet(player&p, int bank);
	int make_bet(player &p1, player &p2);
	int make_bet(player &p1, bot &computer);
	void rethrow_some_dices(player &pl);
	char* start();
	player start_bot();
	player start_human();
	char* start_web();
};

#pragma once
#include "AI.h"
int computer::get_situation()
{
	int result = this->get_combination();
	if (result >= kare)
	{
		return nice;
	}
	else{
		if (result >= big_streit)
		{
			return good;
		}
		else
		{
			if (result >= set_t)
			{
				return normal;
			}
			else
			{
				return bad;

			}
		}
	}
}
int computer::make_bet()
{
	int bet;
    int percent20_gold = get_gold() * 20/100;
    int percent15_gold = get_gold() * 15/100;
    int percent10_gold = get_gold() * 10/100;
    int percent5_gold = get_gold() *5/100;
	int result = this->get_situation();
	if (result == nice)
	{
        bet = rand() % percent20_gold + percent15_gold;
	}
	if (result == good)
	{
        bet = rand() % percent15_gold + percent10_gold;
	}
	if (result == normal)
	{
        bet = rand() % percent10_gold + percent5_gold;
	}
	if (result == bad)
	{
        bet = rand() % percent5_gold + 1;
	}
    if (bet>percent20_gold)
	{
        bet = percent20_gold;
	}
	return bet;
}

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
    int percent40_gold = get_gold() * 40/100;
    int percent30_gold = get_gold() * 30/100;
    int percent20_gold = get_gold() * 20/100;
    int percent10_gold = get_gold() *10/100;
	int result = this->get_situation();
	if (result == nice)
	{
		bet = rand() % percent40_gold + percent30_gold;
	}
	if (result == good)
	{
		bet = rand() % percent30_gold + percent20_gold;
	}
	if (result == normal)
	{
		bet = rand() % percent20_gold + percent10_gold;
	}
	if (result == bad)
	{
		bet = rand() % percent10_gold + 1;
	}
	if (bet>percent40_gold)
	{
		bet = percent40_gold;
	}
	return bet;
}

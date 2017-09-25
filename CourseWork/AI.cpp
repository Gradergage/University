#pragma once
#include "stdafx.h"
#include "AI.h"
int bot::get_situation()
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
int bot::make_bet()
{
	int bet;
	int percent40_gold = gold * 0.4;
	int percent30_gold = gold * 0.3;
	int percent20_gold = gold * 0.2;
	int percent10_gold = gold *0.1;
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
void bot::rethrow_dices()
{
	for (int i = 0; i < 5; i++)
	{
		if (diff_dice[i] != 0)
		{
			throw_dice(i);
		}
	}
}
ostream& operator <<(ostream& out, bot& pl)
{
	out << pl.name << endl;
	for (int i = 0; i < 5; i++)
	{
		out << pl.dices[i].model;
	}
	out << endl;
	return out;
}
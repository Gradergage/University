#include "stdafx.h"
#include "Player.h"
double player::get_combination()
{
	int i, j, k = 0, set = 0, pair = 0; double value = 0, player_priority = 0;
	dice el[5];
	for (i = 0; i < 5; i++)
	{
		el[i].change_value(element[i].value);
	}
	for (i = 1; i <= 5; i++)
	{
		if (!(el[0].value == i || el[1].value == i || el[2].value == i || el[3].value == i || el[4].value == i))
		{
			k = 1;
			break;
		}

	}
	if (k == 0)
	{
		diff_dice[0] = 0;
		diff_dice[1] = 0;
		diff_dice[3] = 0;
		diff_dice[4] = 0;
		diff_dice[5] = 0;
		player_priority = less_streit;
		return player_priority; //малый стрит
	}
	else
	{
		k = 0;
	}
	for (i = 2; i <= 6; i++)
	{
		if (!(el[0].value == i || el[1].value == i || el[2].value == i || el[3].value == i || el[4].value == i))
		{
			k = 1;
			break;
		}

	}
	if (k == 0)
	{
		diff_dice[0] = 0;
		diff_dice[1] = 0;
		diff_dice[3] = 0;
		diff_dice[4] = 0;
		diff_dice[5] = 0;
		player_priority = big_streit; //большой стрит
		return player_priority;
	}
	k = 1;
	int dices[5] = { 1, 1, 1, 1, 1 };
	/*if (el[0].value == el[1].value == el[2].value == el[3].value == el[4].value)
	{
	return poker + value / 10;
	}*/
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (i != j && el[i].value == el[j].value && el[i].value != 0)
			{
				k++; el[j].value = 0;  diff_dice[i] = 0; diff_dice[j] = 0;
			}
		}
		if (k == 3)
		{
			set = 1; value = el[i].value;
		}
		if (k == 2)
		{
			pair++;
			if (el[i].value>value)
			{
				value = el[i].value;
			}
		}
		if (k == 4)
		{
			player_priority = kare + value / 10;
			return player_priority;
		}
		if (k == 5)
		{

			player_priority = poker + value / 10;
			return player_priority;
		}
		k = 1;
	}
	if (set == 1 && pair == 1)
	{
		player_priority = full_house + value / 10;
		return player_priority;
	}
	if (set == 1)
	{
		player_priority = set_t + value / 10;
		return player_priority;
	}
	if (pair == 1)
	{
		player_priority = pair_r + value / 10;
		return player_priority;
	}
	if (pair == 2)
	{
		player_priority = double_pair + value / 10;
		return player_priority;
	}
	if (set == 0 && pair == 0)
	{
		player_priority = nothing + value / 10;
		return player_priority;
	}
	}
void player::throw_dices()
	{
		for (int i = 0; i < 5; i++)
		{
			throw_dice(i);
		}

	}
void player::throw_dice(int number)
{
	int val;

	val = rand() % 6 + 1;

	dices[number].change_value(val);

}
player::player(char* nm)
{
	name = nm;
	for (int i = 0; i < 5; i++)
	{
		diff_dice[i] = 1;
	}
}
ostream& operator <<(ostream& out, player& pl)
	{
		out << pl.name << endl;
		for (int i = 0; i < 5; i++)
		{
			out << pl.dices[i].model;
		}
		out << endl;
		return out;
	}
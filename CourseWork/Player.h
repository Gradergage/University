#pragma once
#include "dice.h"
#include <iostream>
using namespace std;
class player
{
	public:
		char* name;
		int gold = 100;
		dice dices[5];
		dice* element = &dices[0];
		int diff_dice[5];
		player(char* nm);
		void throw_dice(int number);
		void throw_dices();
		double get_combination();	
		friend ostream& operator <<(ostream& out, player& pl);
		friend class bot;

};

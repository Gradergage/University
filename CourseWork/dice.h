#pragma once
#include <iostream>
#include "misc.h"
using namespace std;
enum combinations{ nothing, pair_r, double_pair, set_t, less_streit, big_streit, full_house, kare, poker };
class dice
{
public:
	double value;
	char* model;
	dice(int val = 1);
	void dice::change_value(double val);
	friend std::ostream& operator <<(std::ostream& out, dice& dc);
};

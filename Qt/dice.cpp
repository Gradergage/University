#pragma once
#include "dice.h"
dice::dice(int val)
{
	value = val;
	int vl;
	vl = val;
	model = models[vl - 1];
}
void dice::change_value(double val)
{
	value = val;
	int vl;
	vl = val;
	model = models[vl - 1];
}

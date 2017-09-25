#pragma once
#include "dice.h"
dice::dice(int val)
{
	value = val;
	int vl;
	vl = val;
	model = models[vl - 1];
}

void dice::shape_dice(QPushButton *button)
{
 diceButton=button;
}

void dice::change_value(int val)
{
    value = val;
    model = models[val - 1];
    diceButton->setText(model);
}

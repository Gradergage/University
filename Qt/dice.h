#pragma once
#include "misc.h"
using namespace std;
enum combinations{ nothing, pair_r, double_pair, set_t, less_streit, big_streit, full_house, kare, poker };
class dice
{
public:
    // цена кости
	double value;
    //псевдографическая модель
    QString model;
	dice(int val = 1);
    //изменение ценности кости
    void change_value(double val);
};

#pragma once
#include "Player.h"
enum situation{ bad, normal, good, nice };
class computer : public player
{
public:
    computer(QString name) : player(name)
	{
	}
    //основываясь на функции player::get_combination() дать определение своему положению
    //для последующей ставки. Размер ставки зависит от положения, чем оно хуже, тем ставка ниже
	int get_situation();
    //ставка в зависимости от ситуации
	int make_bet();
};

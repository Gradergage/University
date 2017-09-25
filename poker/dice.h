#pragma once
#include "misc.h"
#include <QPushButton>
using namespace std;
enum combinations{ nothing, pair_r, double_pair, set_t, less_streit, big_streit, full_house, kare, poker };
class dice
{
 private:
    // цена кости
	double value;
    //псевдографическая модель
    QString model;
    QPushButton *diceButton;

 public:
    dice(int val = 1);
    //ассоциировать с кнопкой
    void shape_dice(QPushButton *button);
    //изменение ценности кости вместе с моделью
    void change_value(int val);
    //узнать ценность
    int getvalue() {return value;}
    //изменить ценность
    void editvalue(int vl) {value=vl;}
    //вернуть указатель на кнопку
    QPushButton* get_button() {return diceButton;}
};

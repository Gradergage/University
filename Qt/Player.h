#pragma once
#include "dice.h"
using namespace std;
class player
{
private:
         //имя
        QString name;
        //золото
		int gold = 100;
        //массив костей
		dice dices[5];
        //указатель на массив костей, для последующего изменения в функции
		dice* element = &dices[0];
        //массив костей с данными о парах
        bool diff_dice[5];

public:
        player(QString nm);
        //бросок кости
		void throw_dice(int number);
        //бросок всех костей
		void throw_dices();
        //получение дробного числа отвечающего за ценность комбинации
        double get_combination();
        //информация о кости, имеет ли она пару
        bool if_havent_pair(int index)
        {
            return diff_dice[index];
        }
        //получения значения золота
        int get_gold()
        {
            return gold;
        }
        //изменение золота
        int edit_gold(int summ)
        {
            gold+=summ;
            return gold;
        }
        //получение имени
        QString get_name()
        {
            return name;
        }
        //изменение значения кости с данным индексом
        void change_dice(int value,int index)
        {
            dices[index].change_value(value);
        }
		friend class bot;

};

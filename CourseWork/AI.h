#pragma once
#include "Player.h"
enum situation{ bad, normal, good, nice };
class bot : public player
{
public:
	bot(char* name) : player(name)
	{
	}
	void rethrow_dices();
	//�������� � ������� ����
	int get_situation();
	//��� ������ ������ ����������� �� �������� � �������
	int make_bet();
	friend ostream& operator <<(ostream& out, bot& pl);
};

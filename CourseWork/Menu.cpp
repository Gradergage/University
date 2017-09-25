#include "stdafx.h"
#include "Menu.h"
#include "conio.h"
	//процесс ставок двух игроков, игрок, не согласившийся со ставкой, проигрывает. Второй игрок может повысить ставку
	//resume означает продолжение игры, ставки сделаны правильно
	//Максимально за игру можно потерять 64% игровых денег, чтобы оставалось что-то на дальнейшую игру
	int menu::ask_bet(player&p, int bank)
	{
		int bet = 0;;
		int percent_40_bank = bank*0.4;
		cout << p.name << ", make bet from " << 1 << " to " << percent_40_bank << endl;
		cin >> bet;
		if (bet > percent_40_bank || bet < 1)
		{
			cout << "Try again" << endl;
		}
		return bet;
	}
	int  menu::make_bet(player &p1, player &p2)
	{
		int gold0, gold1 = p1.gold, gold2 = p2.gold;
		char choise = '0';
		gold1 > gold2 ? gold0 = gold2 : gold0 = gold1;
		bet1 = ask_bet(p1, gold0); bet2 = 0;
		while (choise != '1' || choise != '2')
		{
			cout << p2.name << ", do you want to raise the bet? 1-yes/2-no" << endl;
			choise = _getch();

			if (choise == '1')
			{
				/*failed3:
				cout << p2.name << ", make bet from " << 1 << " to " << (int)(gold0 * 0.4) << endl;
				cin >> bet2;
				if (bet2 > (int)(gold0*0.4) || bet2 < 1 || bet2 < bet1)
				{
				cout << "Try again" << endl;
				goto failed3;
				}*/
				while (bet2 < bet1)
				{
					bet2 = ask_bet(p2, gold0);
				}
				bank += bet2;
				p2.gold -= bet2;
				break;
			}
			else
			{
				if (choise == '2')
				{
					bet2 = bet1;
					bank += bet2;
					bank += bet1;
					p2.gold -= bet1;

					break;
				}
			}
		}
		if (bet2 > bet1)
		{
			choise = '0';
			while (choise != '1' || choise != '2')
			{
				cout << p2.name << " raised the bet, " << p1.name << ", do you agree? 1-yes/2-no" << endl;
				choise = _getch();
				if (choise == '1')
				{
					p1.gold -= bet2;
					bet1 = bet2;
					bank += bet2;
					break;
				}
				else
				{
					if (choise == '2')
					{
						p1.gold -= bet2;
						bank += bet2;
						return lose;
					}
				}
			}
		}
		return resume;
	}
	//то же самое, но для бота
	int menu::make_bet(player &p1, bot &computer)
	{

		int gold0;
		char choise;
		p1.gold > computer.gold ? gold0 = computer.gold : gold0 = p1.gold;
		bet1 = ask_bet(p1, gold0);
		bet2 = computer.make_bet();
		if (bet1 >= bet2)
		{
			bet2 = bet1;
			computer.gold -= bet2;
			p1.gold -= bet1;
			bank += bet1 + bet2;
			return resume;
		}
		else
		{
			choise = '0';
			while (choise != '1' || choise != '2')
			{
				cout << computer.name << " raised the bet to " << bet2 << ", " << p1.name << ", do you agree? 1-yes/2-no" << endl;
				choise = _getch();
				if (choise == '1')
				{

					bet1 = bet2;
					p1.gold -= bet1;
					bank += bet2 + bet1;
					computer.gold -= bet2;
					break;
				}
				else
				{
					if (choise == '2')
					{
						bank += bet2;
						return lose;
					}
					break;
				}
			}
		}

		return resume;
	}
	//переброс костей игрока
	void menu::rethrow_some_dices(player &pl)
	{

		printf("%s, enter the numbers of dices which you want to rethrow, please: \n", pl.name);
		char a;
		for (int i = 0; i < 5; i++)
		{
			a = _getch();

		/*	switch (a)
			{
			case '1': pl.throw_dice(a - '0' - 1); printf("%c", a); break;
			case '2': pl.throw_dice(a - '0' - 1); printf("%c", a); break;
			case '3': pl.throw_dice(a - '0' - 1); printf("%c", a); break;
			case '4': pl.throw_dice(a - '0' - 1); printf("%c", a); break;
			case '5': pl.throw_dice(a - '0' - 1); printf("%c", a); break;
			default: i = 11; break;
			}*/
			if (a != '1'&& a != '2'&&a != '3'&&a != '4'&&a != '5')
			{
				break;
			}
			else
			{
				pl.throw_dice(a - '0' - 1); printf("%c", a);
			}

		}
		cout << endl;
	}
	char* menu::start()
	{
		char choise;
		cout << "MENU" << endl << "Play online - 1" << endl << "Play with friend - 2" << endl << "Bot practise - 3" << endl << "Author - 4" << endl << "Exit - 0" << endl;
		choise = _getch();
		if (choise == '1')
		{
			ClearConsole();
			return start_web();
		}
		if (choise == '2')
		{
			ClearConsole();
			player winner = start_human();
			ClearConsole();
			cout << winner.name << " won this game!" << endl << "His gold now: " << winner.gold << endl;
			_getch();
			ClearConsole();
			cout << "Do you want to play again?" << endl << "Yes - 1" << endl << "Exit - press any different button" << endl;
			choise = _getch();
			if (choise == '1')
			{
				ClearConsole();
				return start();
			}
			else
			{
				return 0;
			}
		}
		if (choise == '3')
		{
			ClearConsole();
			player winner = start_bot();
			ClearConsole();
			cout << winner.name << " won this game!" << endl << "His gold now: " << winner.gold << endl;
			_getch();
			ClearConsole();
			cout << "Do you want to play again?" << endl << "Yes - 1" << endl << "Exit - press any different button" << endl;
			choise = _getch();
			if (choise == '1')
			{
				ClearConsole();
				return start();
			}
			else
			{
				return 0;
			}
		}
		if (choise == '4')
		{
			ClearConsole();
			cout << "Pokatilo Pavel, 13501/4" << endl;
			_getch();
			ClearConsole();
			return start();
		}
		if (choise == '0')
		{
			return 0;
		}
		else
		{
			ClearConsole();
			return start();
		}
	}
	player menu::start_bot()
	{
		ClearConsole();
		char *name = new char[20];
		int result;
		cout << "Enter the your name:" << endl;
		cin >> name;
		player plyer(name);
		ClearConsole();
		bot computer("Lucky traveller");
		computer.throw_dices();
		result = make_bet(plyer, computer);
		if (result == lose)
		{
			computer.gold += bank;
			bank = 0;
			return computer;
		}
		ClearConsole();
		plyer.throw_dices();
		cout << plyer;
		computer.throw_dices();
		cout << computer;
		_getch();
		ClearConsole();
		result = make_bet(plyer, computer);
		if (result == lose)
		{
			computer.gold += bank;
			bank = 0;
			return computer;
		}
		ClearConsole();
		rethrow_some_dices(plyer);
		cout << plyer;
		computer.rethrow_dices();
		cout << computer;
		_getch();
		ClearConsole();
		if (plyer.get_combination() > computer.get_combination())
		{
			plyer.gold += bank;
			bank = 0;
			return plyer;
		}
		else
		{
			computer.gold += bank;
			bank = 0;
			return computer;
		}
		return start();
	}
	player menu::start_human()
	{
		char *name = new char[20];
		int result;
		cout << "Enter the player 1 name:" << endl;
		cin >> name;
		player p_one(name);
		ClearConsole();
		cout << "Enter the player 2 name:" << endl;
		char *name2 = new char[20];
		cin >> name2;
		player p_sec(name2);
		ClearConsole();
		result = make_bet(p_one, p_sec);
		if (result == lose)
		{
			p_sec.gold += bank;
			bank = 0;
			return p_sec;
		}
		ClearConsole();
		p_one.throw_dices();
		cout << p_one;
		p_sec.throw_dices();
		cout << p_sec;
		_getch();
		ClearConsole();
		result = make_bet(p_one, p_sec);
		if (result == lose)
		{
			p_sec.gold += bank;
			bank = 0;
			return p_sec;
		}
		ClearConsole();
		rethrow_some_dices(p_one);
		cout << p_one;
		rethrow_some_dices(p_sec);
		cout << p_sec;
		_getch();
		ClearConsole();
		if (p_one.get_combination() > p_sec.get_combination())
		{
			p_one.gold += bank;
			bank = 0;
			return p_one;
		}
		else
		{
			p_sec.gold += bank;
			bank = 0;
			return p_sec;
		}


	}
	char* menu::start_web()
	{
		ClearConsole();
		cout << "Not avalible";
		_getch();
		ClearConsole();
		return start();
	}

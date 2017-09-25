#include "stdafx.h"
#include <clocale>
#include <ctime>
#include "menu.h"
#include "resource.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	 
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	menu main;
	main.start();
	return IDR_MENU1;
};
#pragma once
#include <windows.h>
static char* playerdata;
static char * models[] = { " --- \n|   |\n| o |\n|   |\n --- \n", " --- \n|  o|\n|   |\n|o  |\n --- \n", " --- \n|  o|\n| o |\n|o  |\n --- \n", " --- \n|o o|\n|   |\n|o o|\n --- \n", " --- \n|o o|\n| o |\n|o o|\n --- \n", " --- \n|o o|\n|o o|\n|o o|\n --- \n" };
enum WinLoseStatus{ win, lose, resume };
static void ClearConsole()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD written;
	COORD zeroPos = { 0, 0 };

	if (GetConsoleScreenBufferInfo(consoleHandle, &csbi))
	{
		DWORD numChars = csbi.dwSize.X * csbi.dwSize.Y;

		FillConsoleOutputCharacter(consoleHandle, ' ', numChars, zeroPos, &written);
		FillConsoleOutputAttribute(consoleHandle, csbi.wAttributes, numChars, zeroPos, &written);
	}
	SetConsoleCursorPosition(consoleHandle, zeroPos);
}
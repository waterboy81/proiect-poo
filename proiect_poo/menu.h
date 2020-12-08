#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pozitie;

void gotoXY(int x, int y)
{
	pozitie.X = x;
	pozitie.Y = y;
	SetConsoleCursorPosition(consola, pozitie);
}
int x = 1;
int optiune=0;
bool sem = true;
void meniu()
{
	gotoXY(1, 2);
	cout << "MENIU";
	gotoXY(6, 2);
	cout << "-->\n";
	while (sem)
	{
		gotoXY(10, 2);
		cout << "1) Tabele existente";
		gotoXY(10, 3);
		cout << "2) Comenzi disponibile";
		gotoXY(10, 4);
		cout << "3) Inchide";
		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && x != 4)
		{
			gotoXY(32, x);
			cout << "  ";
			x++;
			gotoXY(32, x);
			optiune++;
			cout << "<";
		}
		if (GetAsyncKeyState(VK_UP) && x != 2)
		{
			gotoXY(32, x);
			cout << "  ";
			x--;
			gotoXY(32, x);
			optiune--;
			cout << "<";
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			switch (optiune)
			{
			case 1:
			{
				gotoXY(2, 8);
				cout << "Tabelele existente: ";
				break;
			}
			case 2:
			{
				gotoXY(2, 8);
				cout << "Comenzi existente:";
				break;
			}
			case 3:
			{
				gotoXY(2, 8);
				cout << "Meniul se va inchide";
				sem = false;
			}
			}
		}
	}
};
// proiect_poo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include "menu.h";
using namespace std;

class Table {
protected:
	vector<string> lista_tabele;//pt a tine minte tabelele create
	int nr_tabele = 0;
public:
	string nume_tabela;
	int nr_coloane;
	string** info_col;
	//0-nume coloane
	//1-tip
	//2-dimensiune
	//3-valoare implicita

	Table() {
		nume_tabela = "nedefinit";
		nr_coloane = 0;
	}

	//Table(string nume_tabela, int nr_coloane) {
	//	this->nume_tabela = nume_tabela;
	//	this->nr_coloane = nr_coloane;
	//	nr_tabele++;
	//	lista_tabele.push_back(nume_tabela);
	//}

	void Create_Table(string nume_tabela, int nr_coloane)
	{
		this->nume_tabela = nume_tabela;
		this->nr_coloane = nr_coloane;
		nr_tabele++;
		lista_tabele.push_back(nume_tabela);
		info_col = new string * [3];

		for (int i = 0; i < 3; i++)
		{
			info_col[i] = new string[1000];
		}
		for (int i = 0; i < nr_coloane; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (j == 0) cout << "nume coloana " << i + 1 << ": ";
				if (j == 1) cout << "tip date: ";
				if (j == 2) cout << "dimensiune: ";
				if (j == 3) cout << "valoare implicita: ";
				cin >> info_col[i][j];
			}
		}
	}

	void DESC_TABLE(string nume_tabela)
	{
		for (int i = 0; i < nr_coloane; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (j == 0)
				{
					cout << "nume coloana " << i + 1 << ": ";
					cout << info_col[i][j] << " \n";
				}
				if (j == 1)
				{
					cout << "tip date: ";
					cout << info_col[i][j] << " \n";
				}
				if (j == 2)
				{
					cout << "dimensiune: ";
					cout << info_col[i][j] << " \n";
				}
				if (j == 3)
				{
					cout << "valoare implicita: ";
					cout << info_col[i][j] << " \n";
				}
			}
		}
	}

	void Arata_lista()
	{
		for (int i = 0; i < lista_tabele.size(); i++)
			cout << lista_tabele[i];
	}

	void DROP_TABLE(string nume_tabela)
	{
		for (int i = 0; i < nr_coloane; i++)
			for (int j = 0; j < 4; j++)
				info_col[i][j] = "";
	}

};

int main()
{
	Table a;
	a.Create_Table("a", 1);
	a.DESC_TABLE("a");
	a.DROP_TABLE("a");
	a.DESC_TABLE("a");
}

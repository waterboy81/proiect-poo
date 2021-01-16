#pragma once
#include <iostream>
#include<string>
#include <fstream>
#include <cstdio>
#include "Table.h"
#include "Comanda.h"

using namespace std;

class drop_table : public comanda
{

public:

	drop_table() {}

	drop_table(string cmd) : comanda(cmd) {}


	void drop(vector <Table>& list_tabele)
	{
		int ok = 0; string s = getname();
		if (this->getnb() == 1)
		{
			for (int i = 0; i < list_tabele.size(); i++)
			{
				if (list_tabele[i].getNume_tabela() == s)
				{
					list_tabele.erase(list_tabele.begin() + i);
					string file_name = s + ".bin";
					remove(file_name.c_str()); //sterge fisierul asociat
					ok = 1;
				}
			}
		}
		if (ok == 1)
		{
			cout << endl << "Table " << s << " has been dropped ." << endl << endl;
		}
		else
		{
			cout << "ERROR from drop_table -> tabela " << s << " nu se afla in baza de date" << endl << endl;
		}
	}


	void display_table(vector <Table> lista_tabele)
	{
		int ok = 0;
		for (int i = 0; i < lista_tabele.size(); i++)
		{
			if (lista_tabele[i].getNume_tabela().compare(this->getname()) == 0)
			{
				cout << lista_tabele[i];
				cout << endl << "Table " << this->getname() << " has been displayed " << endl;
				cout << "___________________________________" << endl << endl;
				ok = 1;
			}
		}
		if (ok == 0)
		{
			cout << endl << "Display_table -> comanda introdusa gresit sau tabela nu exista in baza de date" << endl;
			cout << "tabela specificata in comanda a fost " << this->getname() << endl << endl;
		}

	}

};
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
					file_name = s + "_data.bin";
					remove(file_name.c_str());  //sterge fisierul de date asociat
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

	void raport_display(Table t) 
	{	
		string s = getname();
		ofstream g;
		g.open(s + "_display.txt", ios::out|ios::ate);
		if (g.is_open()) 
		{
			g << "DISPLAY RETURNED "<<endl<<endl;
			g << "Nume tabela : "<< t.getNume_tabela()<<" ( "<<t.getNr_coloane()<<" coloane )"<<endl<<endl;
			g << "COLOANE TABELA : " << endl; 
			for (int i = 0; i < t.getNr_coloane(); i++) 
			{
				g <<"Nume coloana : "<< t.getcol()[i].getNume()<<" ||  Restrictii : ";
					g <<" Type: "<< t.getcol()[i].getRestrictii().getType()<<" ";
					g <<" Size: "<< t.getcol()[i].getRestrictii().getSize() << " ";
					g <<" Default " << t.getcol()[i].getRestrictii().getVal_predefinita() << " "<<endl;
			}
			g << endl << "Table " << this->getname() << " has been displayed " << endl;
		}
	}

	bool corect(vector <Table> lista_tabele)
	{
		for (int i = 0; i < lista_tabele.size(); i++)
		{
			if (lista_tabele[i].getNume_tabela().compare(this->getname()) == 0)
			{
				return true;
			}
		}

		return false;
	}


	void display_table(vector <Table> lista_tabele)
	{
		int ok = 0;
		for (int i = 0; i < lista_tabele.size(); i++)
		{
			if (corect(lista_tabele)==1)
			{
				cout << lista_tabele[i];
				cout << endl << "Table " << this->getname() << " has been displayed " << endl;
				cout << "___________________________________" << endl << endl;
				raport_display(lista_tabele[i]);
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
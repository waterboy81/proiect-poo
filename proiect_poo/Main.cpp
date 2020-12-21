// proiect_poo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Table.h"
#include "Functii.h"
//#include "menu.h"


using namespace std;

vector <Table> lista_tabele;   //->lista mea de tabele
vector <string> data;		   //->folosit pentru trecerea de la comanda in consola -> coloana
vector <coloana> coloane;	   //->salveaza coloanele dupa fiecare apel de getline (in prelucrari)

//IMPORTANT, am implementat ca atunci cand se arunca exceptie,
//Sa arate ce metoda a aruncat exceptia (pentru a putea fi mai usor cu debugger-ul)
// sintaxa :: nume_metoda -> exceptie


	//LISTA TABELE
void display_list()
{
	cout << "Tabele din baza de date sunt: " << endl;

	for (size_t i = 0; i < lista_tabele.size(); i++)
	{

		cout << i << " ." << lista_tabele[i].nume_tabela << " " << endl;
	}
}

//DROP TABLE
void drop_table(string nume_tabela, vector <Table> &lista_tabele) // & salveaza modificarile asupra listei
{
	for (size_t i = 0; i < lista_tabele.size(); i++)
	{
		if (nume_tabela.compare(lista_tabele[i].nume_tabela) == 0)
		{
			lista_tabele.erase(lista_tabele.begin() + i);
		}
	}

	cout << "Table " << nume_tabela << " has been dropped ." << endl;
	cout << endl;
}


//CREATE TABLE
void create_table(string comanda, vector <Table>& lista_tabele)
{
	string name = table_name(comanda);
	string s = info_coloane(comanda);
	int nr = nr_coloane(comanda);

	vector <string> data = data_coloane(s, nr);
	vector <coloana> coloane = coloane_tabela(comanda, nr, data);

	if (coloane.begin() != coloane.end()) {
		Table Instance(name, nr, lista_tabele, coloane);
		cout << "Tabela " << name << " has been created " << endl;
	}
	else
		throw exception("create table -> Comanda nu a fost introdusa corect (verificati ca aveti mai mult de o coloana)");
}

//DISPLAY TABLE -> afiseaza structura tabelei prin supraincarea lui <<
void display_table(int cod, string nume_tabela, vector <Table> lista_tabele)
{
	if (cod == 2)
	{
		for (size_t i = 0; i < lista_tabele.size(); i++)
		{
			if (lista_tabele[i].nume_tabela.compare(nume_tabela) == 0)
			{
				for (size_t j = 0; j < lista_tabele.size(); j++)
				{
					cout << lista_tabele[j] << endl;
				}
			}
		}
	}

	else
		throw exception("display_table -> comanda introdusa gresit sau tabela nu exista in baza de date");
}


int main()
{
	string comanda;
	//scriere in fisier::
	/*ofstream myfile;
	myfile.open("Comenzi_consola.txt", ios::app | ios::out);
	cout << "Introduceti comenzile (pentru a va opri, introduceti un rand gol)"<<endl;
	while (getline(cin, comanda) && comanda != "")
	{
		myfile << comanda<<endl;
	}

	myfile.close();*/

	ifstream c;
	c.open("Comenzi_consola.txt");
	while (getline(c, comanda))
	{
		create_table(comanda, lista_tabele);
	}

	c.close();
	display_list();


	/*try
	{
		//Am testat create table pe o serie de instructiuni, succesive (merge)
		cout << "Introduceti comanda pentru create: ";
		for (int i = 0; i < 1; i++)
		{
			getline(cin, comanda);
			create_table(comanda, lista_tabele);

		}


		//cout << "Introduceti comanda" << endl;
		//getline(cin, comanda);
		//create_table(comanda, lista_tabele);
		display_list();
		//--drop la precedenta creata (doar ca sa vad drop-ul)
		//drop_table(table_name(comanda), lista_tabele);

		//cout << "Introduceti comanda pentru display:";
		//getline(cin, comanda);
		//display_table(identificare_comanda(comanda), table_name(comanda),lista_tabele);

	}

	catch (exception e)
	{
		cout << e.what();
	}
	catch (...)
	{
		cout << "Nici nu mi pot imagina cum a mai crapat xmemory.." << endl;
	}*/

}

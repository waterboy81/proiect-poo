#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Table.h"
#include "Functii.h"

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

		cout << i << " ." << lista_tabele[i].getNume_tabela() << " " << endl;
	}

	cout << endl;
}

//DROP TABLE
void drop_table(string comanda, vector <Table>& lista_tabele) // & salveaza modificarile asupra listei
{
	int ok = 0;
	string nume_tabela = table_name(comanda);
	for (size_t i = 0; i < lista_tabele.size(); i++)
	{
		if (nume_tabela.compare(lista_tabele[i].getNume_tabela()) == 0)
		{
			lista_tabele.erase(lista_tabele.begin() + i);
			ok = 1;
		}
	}
	if (ok == 1)
	{
		cout << endl << "Table " << nume_tabela << " has been dropped ." << endl << endl;
	}
	else
	{
		cout << "ERROR from drop_table -> tabela " << nume_tabela << " nu se afla in baza de date" << endl << endl;
	}
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
		cout << endl << "ERROR from create table -> Comanda nu a fost introdusa corect (verificati ca aveti mai mult de o coloana)" << endl;
}

//DISPLAY TABLE -> afiseaza structura tabelei prin supraincarea lui <<
void display_table(string comanda, vector <Table> lista_tabele)
{
	int ok = 0;
	string nume_tabela = table_name(comanda);
	for (size_t i = 0; i < lista_tabele.size(); i++)
	{
		if (lista_tabele[i].getNume_tabela().compare(nume_tabela) == 0)
		{
			cout << lista_tabele[i];
			cout <<endl<< "Table " << nume_tabela << " has been displayed " << endl;
			cout << "___________________________________" << endl << endl;
			ok = 1;
		}
	}
	if (ok == 0)
	{
		cout << endl << "ERROR from display_table -> comanda introdusa gresit sau tabela nu exista in baza de date" << endl;
		cout << "comanda display_table este formatata sa primeasca numele tabelei fara space dupa aceasta" << endl;
		cout << "tabela specificata in comanda a fost " << nume_tabela << endl << endl;
	}

}

//INSERT INTO 

void insert_into(string comanda)
{
	if (identificare_comanda(comanda) == 5) {
		string nume = table_name(comanda);

		for (unsigned int i = 0; i < lista_tabele.size(); i++)
		{
			if (lista_tabele[i].getNume_tabela() == nume)
			{
				string* s = valori(comanda, lista_tabele[i].getNr_coloane());
				for (int j = 0; j < lista_tabele[i].getNr_coloane(); j++)
				{
					lista_tabele[i].getColoane_tabela()[j].add_values(s[j], 1);
				}

			}
		}

		cout << "Values successfully added to database in table " << nume << endl;
	}

	else
		cout << "ERROR from insert_table -> comanda formatata gresit" << endl;

}


//DELETE_FROM

void delete_from(string comanda)
{
	string n_tabela = table_name(comanda);
	string n_coloana = nume_coloana(comanda);
	string to_delete = value(comanda);
	int ok = 0; int contor = 0;
	for (unsigned int i = 0; i < lista_tabele.size(); i++)
	{
		if (lista_tabele[i].getNume_tabela() == n_tabela)
		{
			for (int j = 0; j < lista_tabele[i].getNr_coloane(); j++)
			{
				if (lista_tabele[i].getColoane_tabela()[j].getNume() == n_coloana)
				{
					for (int k = 0; k < lista_tabele[i].getColoane_tabela()[j].getNb_values(); k++)
					{
						if (lista_tabele[i].getColoane_tabela()[j].getValues()[k] == to_delete)
						{
							lista_tabele[i].modificare_date(k);
							ok = 1;
							k--;
							contor++;
						}
					}
				}
			}
		}
	}

	if (ok == 1)
	{
		cout << "Changes have been applied to table " << n_tabela << ". " << endl << contor << " rows deleted. ";
		cout << "Inregistrarile corespondente lui -> " << to_delete << " <- au fost sterse din baza de date ." << endl;
		cout << endl;
	}

	else {
		cout << "ERROR from delete_from -> comanda formatata gresit sau in tabela nu exista inregistrari " << endl;
		cout << "Detalii comanda introdusa -> nume_tabel= " << n_tabela << " nume_coloana= " << n_coloana << " valoare= " << to_delete << endl;
		cout << endl;
	}
}




//SELECT

void select(string comanda)
{
	int nr_coloane = nr_select(comanda);
	string* coloane_selectate = coloane_name(comanda, nr_coloane);
	string n_tabela = table_name(comanda);
	int ok = 0;
	for (unsigned int i = 0; i < lista_tabele.size(); i++)
	{
		if (lista_tabele[i].getNume_tabela() == n_tabela)
		{
			ok = 1;
			cout << "SELECT returned -> " << endl;
			for (int t = 0; t < nr_coloane; t++)
			{
				for (int j = 0; j < lista_tabele[i].getNr_coloane(); j++)
				{
					if (lista_tabele[i].getColoane_tabela()[j].getNume() == coloane_selectate[t])
					{
						cout << "NUME COLOANA: " << lista_tabele[i].getColoane_tabela()[j].getNume() << endl;
						for (int k = 0; k < lista_tabele[i].getColoane_tabela()[j].getNb_values(); k++)
						{
							cout << lista_tabele[i].getColoane_tabela()[j].getValues()[k] << endl;
						}

						cout << endl;
					}
				}
			}

		}
	}

	if (ok == 1)
	{
		cout  << "Values from table " << n_tabela << " have been desplayed" << endl;
	}

	else
		cout << "ERROR -> SELECT nu a putut identifica comenzile / tabela in baza de date" << endl;
}


//SELECT ALL FROM

void select_all(string comanda)
{
	string n_tabela = table_name(comanda);
	int ok = 0;
	for (unsigned int i = 0; i < lista_tabele.size(); i++)
	{
		if (lista_tabele[i].getNume_tabela() == n_tabela)
		{
			ok = 1;
			cout << "SELECT ALL returned -> " << endl;
			for (int j = 0; j < lista_tabele[i].getNr_coloane(); j++)
			{
				cout << "NUME COLOANA: " << lista_tabele[i].getColoane_tabela()[j].getNume() << endl;
				for (int k = 0; k < lista_tabele[i].getColoane_tabela()[j].getNb_values(); k++)
				{
					
					cout << lista_tabele[i].getColoane_tabela()[j].getValues()[k] << endl;
				}

				cout << endl;
			}

		}
	}

	if (ok == 1)
	{
		cout << "Values from table " << n_tabela << " have been displayed" << endl;
		cout  << endl;
	}

	else
	{
		cout << "____________________________________" << endl;
		cout << "ERROR from select_all -> tabela nu exista in baza de date sau nu exista inregistrari" << endl;
		cout << "Detalii comanda introdusa: table_name= " << n_tabela << endl;
		cout << endl;
	}
}


//UPDATE
void update(string comanda)
{
	string n_table = table_name(comanda);
	string n_coloana = nume_update(comanda);
	string change = new_value(comanda);
	string to_change = old_value(comanda);

	int ok = 0; int contor = 0;
	for (unsigned int i = 0; i < lista_tabele.size(); i++)
	{
		if (lista_tabele[i].getNume_tabela() == n_table)
		{
			ok = 1;
			for (int j = 0; j < lista_tabele[i].getNr_coloane(); j++)
			{
				if (lista_tabele[i].getColoane_tabela()[j].getNume() == n_coloana) 
				{
					for (int k = 0; k < lista_tabele[i].getColoane_tabela()[j].getNb_values(); k++)
					{
						if (lista_tabele[i].getColoane_tabela()[j].getValues()[k] == to_change) 
						{
							lista_tabele[i].getColoane_tabela()[j].setValue(change, k);
							contor++;
						}
					}

				}
			}
		}
	}

	if (ok == 1 && contor!=0) 
	{
		cout << endl << "Table " << n_table << " has been altered.";
		cout << endl << contor << " row / rows have been updated. " << endl;
		cout << endl;
	}

	else 
	{
		cout << "____________________________________" << endl;
		cout << "ERROR: UPDATE TABLE nu a regasit tabela/ coloana sau valoarea specificata in baza de date" << endl;
		cout << "Date introduse:"<<endl<< "nume_tabela-> " << n_table << endl;
		cout << "nume_coloana-> " << n_coloana << endl;
		cout << "valoare_inregistrare-> " << to_change << endl;
		cout<<"valore_noua-> " << change << endl;
		cout << endl;
	}

}


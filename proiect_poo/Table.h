#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Coloana.h"
using namespace std;


class Table
{
private:
	string nume_tabela = "";
	int nr_coloane = 0;
	vector <coloana> coloane_tabela;
	friend ostream& operator<<(ostream&, Table);
	friend istream& operator>>(istream&, Table t);
public:
	//getteri si setteri
	string getNume_tabela()
	{
		return nume_tabela;
	}
	void setNume_tabela(string nume_tabela)
	{
		this->nume_tabela = nume_tabela;
	}

	int getNr_coloane()
	{
		return nr_coloane;
	}
	void setNr_coloane(int nr_coloane)
	{
		this->nr_coloane = nr_coloane;
	}

	  vector <coloana>& getColoane_tabela()
	{
		return coloane_tabela;
	}
	void setColoane_tabela(vector<coloana> &coloane_tabela)
	{
		this->coloane_tabela = coloane_tabela;
	}
	//final getteri si setteri
	//supraincarcare pt1
	bool operator!()
	{
		return nr_coloane > 0;
	}
	Table operator++()
	{
		this->nr_coloane++;
		return *this;
	}
	Table operator++(int i)
	{
		Table copie = *this;
		this->nr_coloane++;
		return *this;
	}
	Table operator+(int valoare)
	{
		Table copie = *this;
		copie.nr_coloane += valoare;
		return copie;
	}
	explicit operator int()
	{
		return nr_coloane;
	}
	int operator()()
	{
		if (nume_tabela != "")
			return nume_tabela.size();
		else
			return 0;
	}
	int operator==(Table& t)
	{
		if (this->nume_tabela == t.nume_tabela) return true;
		else return false;
	}
	int operator>=(Table& t)
	{
		if (this->nr_coloane >= t.nr_coloane) return true;
		else return false;
	}
	//final supraincarcare pt 1


	Table() {}

	Table(string nume_tabela, int nr_coloane, vector<Table>& lista_tabele)
	{

		int ok = 1;          //verificare cu tabele deja existente / conditia {if not exist}

		if (lista_tabele.size() > 0)
		{
			//size_t pentru warning de signed/unsigned (iterators)
			for (size_t i = 0; i < lista_tabele.size(); i++) {
				if (nume_tabela.compare(lista_tabele[i].nume_tabela) == 0)
				{
					ok = 0;
				}
			}
		}

		if (ok == 1)
		{
			this->nume_tabela = nume_tabela;
			this->nr_coloane = nr_coloane;

		}

		else //cazul cand numele tabelei nu corespunde bazei de date
		{
			this->nr_coloane = nr_coloane;
			throw exception("constructor Table -> Numele introdus este folosit deja");
		}

		lista_tabele.push_back(*this);

	}


	Table(string nume_tabela, int nr_coloane, vector<Table>& lista_tabele, vector<coloana>& c_tabela)
	{

		int ok = 1;

		if (lista_tabele.size() > 0)
		{
			for (size_t i = 0; i < lista_tabele.size(); i++) {
				if (nume_tabela.compare(lista_tabele[i].nume_tabela) == 0)
				{
					ok = 0;
				}
			}
		}


		if (ok == 1)
		{
			this->nume_tabela = nume_tabela;
			this->nr_coloane = nr_coloane;
		}

		else
		{
			this->nr_coloane = nr_coloane;

			throw exception("constructor Table -> Numele introdus este folosit deja");
		}

		//inventie Iulia

		vector<coloana>::iterator it; //daca nici nu iterator nu merge, ma las de facultate
		for (it = c_tabela.begin(); it < c_tabela.end(); it++)
		{
			this->coloane_tabela.push_back(*it);    //.at() face o verificare de out-of-range 
													//in plus fata de [] ->nu ti crapa memory macar
		}

		lista_tabele.push_back(*this);

	}

	~Table()
	{

	}

};
//supraincarcare pt2
ostream& operator<<(ostream& out, Table t)
{
	cout << endl << "___________________________________" << endl;
	cout << "Nume tabel=";
	out << t.nume_tabela << endl;
	cout << "Numarul de coloane=";
	out << t.nr_coloane << endl;
	for (int i = 0; i < t.nr_coloane; i++)
	{
		cout << endl;
		cout << i + 1 << ". ";
		out << t.coloane_tabela[i];
	}

	return out;

}
istream& operator>>(istream& in, Table t)
{
	in >> t.nume_tabela;
	in >> t.nr_coloane;
	for (int i = 0; i < t.nr_coloane; i++)
	{
		in >> t.coloane_tabela[i];
	}
	return in;
}

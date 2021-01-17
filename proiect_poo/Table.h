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
	coloana* coloane = NULL;

	friend ostream& operator<<(ostream&, Table);
	friend istream& operator>>(istream&, Table t);

public:

	Table() {}

	//CONSTRUCTOR NOU si bun
	Table(string nume_tabela, int nr_coloane, vector<Table>& lista_tabele, coloana* c_tabela)
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
			cout << "Error Table -> Numele introdus este folosit deja" << endl;
		}

		if (c_tabela != NULL && nr_coloane != 0)
		{
			if (coloane == NULL)
			{
				delete[] coloane;
				this->nr_coloane = nr_coloane;
				this->coloane = new coloana[nr_coloane];
				for (int i = 0; i < nr_coloane; i++)
				{
					this->coloane[i] = c_tabela[i];
				}
			}
		}

		if (ok == 1)
		{
			lista_tabele.push_back(*this);
			cout << "Table " << nume_tabela << " created ." << endl;
		}

	}

	//constructor from binary
	Table(string nume_tabela, int nr_coloane, vector<Table>& lista_tabele, vector<coloana> c_tabela)
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
			coloane = new coloana[nr_coloane];
			for (int i = 0; i < nr_coloane; i++)
			{
				coloane[i] = c_tabela[i];
			}

			lista_tabele.push_back(*this);

		}

	}


	//inventie pentru delete_from metoda de decalare
	void modificare_date(int row)				//row->row to be deleted in table
	{

		for (int i = 0; i < nr_coloane; i++)
		{
			for (int j = 0; j < coloane[i].getNb_values(); j++)
			{
				if (j == row)
				{
					for (int k = j; k < coloane[i].getNb_values(); k++)
					{
						coloane[i].getValues()[k] = coloane[i].getValues()[k + 1];
					}
				}
			}
			coloane[i].setNb_values(coloane[i].getNb_values() - 1);
		}
	}


	Table& operator=(const Table& t)
	{
		nume_tabela = t.nume_tabela;
		if (this->coloane != NULL)
		{
			delete[] coloane;
		}
		if (t.coloane != NULL)
		{
			nr_coloane = t.nr_coloane;
			coloane = new coloana[nr_coloane];
			for (int i = 0; i < nr_coloane; i++)
			{
				coloane[i] = t.coloane[i];
			}
		}
		else
		{
			nr_coloane = 0;
			coloane = NULL;
		}

		return *this;
	}

	Table(const Table& t)
	{
		nume_tabela = t.nume_tabela;
		if (t.coloane != nullptr && t.nr_coloane != 0)
		{
			this->nr_coloane = t.nr_coloane;
			this->coloane = new coloana[nr_coloane];
			for (int i = 0; i < nr_coloane; i++)
			{
				this->coloane[i] = t.coloane[i];
			}
		}
		else
		{
			this->coloane = nullptr;
			this->nr_coloane = 0;
		}
	}


	//functii acces 

	string getNume_tabela()
	{
		return nume_tabela;
	}

	coloana* getcol()
	{
		if (coloane != NULL)
		{
			return &coloane[0];
		}
	}

	void set_csv(vector<string> values) 
	{
		if (values.size() % nr_coloane == 0)
		{
			int j = 0;
			while (j < values.size())
			{
				for (int i = 0; i < nr_coloane; i++)
				{
					coloane[i].add_values(values[j], 1);
					j++;
				}
			}
		}

		else
			cout << "Fisierul csv nu corespunde definitiei tabelei." << endl;
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


	//supraincarcari operatori pt1

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

	~Table()
	{
		if (coloane != NULL)
		{
			delete[] coloane;
		}
	}

};

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
		out << t.coloane[i];
	}

	return out;

}
istream& operator>>(istream& in, Table t)
{
	in >> t.nume_tabela;
	in >> t.nr_coloane;
	for (int i = 0; i < t.nr_coloane; i++)
	{
		in >> t.coloane[i];
	}
	return in;
}

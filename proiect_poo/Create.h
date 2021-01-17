#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Table.h"
#include "Comanda.h"

using namespace std;

class comanda_create : public comanda
{
private:

	coloana* datas = NULL;
	int size = 0;

public:
	comanda_create()
	{
		coloana* datas = NULL;
		int size = 0;
	}

	comanda_create(string cmd) : comanda(cmd)
	{
		this->identificare_comanda();
		this->table_name();
		this->define_coloane();
	}

	comanda_create& operator=(const comanda_create& c)
	{
		if (c.datas != NULL)
		{
			if (this->datas != NULL)
			{
				delete[] this->datas;
				this->size = c.size;
				this->datas = new coloana[size];
				for (int i = 0; i < size; i++) {
					this->datas[i] = c.datas[i];
				}
			}
		}

		return *this;
	}

	int getsize()
	{
		return this->size;
	}

	coloana* getcon()
	{
		if (this->datas != NULL)
		{
			coloana* copie = new coloana[this->size];
			for (int i = 0; i < size; i++)
			{
				copie[i] = datas[i];
			}

			return copie;
		}

		else
		{
			return NULL;
		}
	}


	bool operator!()
	{
		if (this->getnb() == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	void define_coloane()
	{
		int ok = 0; unsigned int sum = 0;
		string c = getcmd();
		c = c.substr(c.find(this->getname()) + this->getname().size());
		c.erase(remove(c.begin(), c.end(), ' '), c.end());
		bool corect = !*this;
		if (this->getnb() == 0 && corect == 1)
		{
			if (this->datas != NULL)
			{
				delete[] datas;
			}
			sum += count(c.begin(), c.end(), '(');
			sum += count(c.begin(), c.end(), ')');

			if (sum % 2 == 0 && sum / 2 > 1 && sum != 0)
			{
				ok = 1;
			}

			//EXTRAG PARTEA DE COMENZI

			if (ok == 1)
			{
				c = c.substr(c.find("(") + 1, c.find_last_of(")"));
				this->size = (sum - 2) / 2;
				this->datas = new coloana[size];

				for (int i = 0; i < size; i++)
				{
					string* coloane_info = new string[4];
					string x = c.substr(c.find("(") + 1, c.find(")"));
					int dimensiune = x.length();

					string s = x.substr(0, x.find(","));
					coloane_info[0] = s;

					x = x.substr(x.find(",") + 1, x.find(")"));
					s = x.substr(0, x.find(","));
					coloane_info[1] = s;

					x = x.substr(x.find(",") + 1, x.find(")"));
					s = x.substr(0, x.find(","));
					coloane_info[2] = s;

					x = x.substr(x.find(","), x.find(")"));
					s = x.substr(x.find(",") + 1, x.find(")") - 1);
					coloane_info[3] = s;

					c.erase(0, dimensiune + 1);

					//create coloane
					constraints restrictii(coloane_info[1], coloane_info[2], coloane_info[3]);
					coloana col(coloane_info[0], restrictii);

					datas[i] = col;
					delete[] coloane_info;
				}
			}
		}
	}

	void create(vector <Table>& list_tabele)
	{
		if (datas != NULL && getnb() != -1 && getname() != "")
		{
			Table Instance(getname(), size, list_tabele, datas);
			this->WriteBinaryFile(Instance);

		}

		else
			cout << "Comada CREATE TABLE formatata gresit" << endl;
	}

	void create_binary()
	{
		//
	}


	void WriteBinaryFile(Table t)
	{
		string nume_fisier = t.getNume_tabela();
		ofstream f(nume_fisier + ".bin", ios::out | ios::binary | ios::trunc);
		int l;
		if (!f.is_open())
			cout << "Nu se poate deschide fisierul " << nume_fisier << endl;
		else
		{
			l = t.getNume_tabela().length();
			f.write((char*)&l, sizeof(l));
			l = l + 1;
			f.write(t.getNume_tabela().c_str(), l);  //ma rog sa nu faca figuri usigned ul din length

			for (int i = 0; i < t.getNr_coloane(); i++)
			{
				l = t.getcol()[i].getNume().length();
				f.write((char*)&l, sizeof(l));
				l = l + 1;
				f.write(t.getcol()[i].getNume().c_str(), l);

				l = t.getcol()[i].getRestrictii().getType().length();
				f.write((char*)&l, sizeof(l));
				l = l + 1;
				f.write(t.getcol()[i].getRestrictii().getType().c_str(), l);

				l = t.getcol()[i].getRestrictii().getSize();
				f.write((char*)&l, sizeof(l));


				l = t.getcol()[i].getRestrictii().getVal_predefinita().length();
				f.write((char*)&l, sizeof(l));
				l = l + 1;
				f.write(t.getcol()[i].getRestrictii().getVal_predefinita().c_str(), l);
				f.clear();
			}

			//f.write((char*)&t, sizeof(Table));
			//nu e optim la deserializare 
		}
		f.close();
	}


	~comanda_create()
	{
		if (datas != NULL)
		{
			delete[] datas;
		}
	}
};
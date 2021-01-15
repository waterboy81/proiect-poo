#pragma once
#include <iostream>
#include <string>
#include "Table.h"
#include "Comanda.h"

using namespace std;

vector <Table> list_tabele;

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

	//ACCES
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


	/*void identificare_comanda()
	{
		const char* commands[10] = { "CREATE TABLE ","DROP TABLE ", "DISPLAY TABLE ", "CREATE INDEX ", "DROP INDEX ", "INSERT INTO ", "DELETE FROM ","SELECT ALL FROM ", "SELECT ", "UPDATE " };
		size_t position = -1;  int ok = 0; int val = -1;

		for (int i = 0; i < 10 && ok == 0; i++)
		{
			string define = (char*)commands[i];
			position = this->getcmd().find(define);
			if (position != 0 && ok == 0)
			{
				ok = 0;
			}
			else
			{
				ok = 1;
				val = i;
			}

		}


		if (val == -1)
		{
			cout << "identificare_comanda -> Comanda introdusa gresit SAU posibilitatea ca in .txt sa fie randuri goale" << endl;
		}

		else
		{
			this->nr = val;
		}
	}

	void name()
	{
		if (nr == 0)
		{
			string str2;
			string c = "CREATE TABLE ";
			size_t position = this->comanda_introdusa.find(c);
			str2 = comanda_introdusa.substr(position + c.length());
			string str3 = str2.substr(0, str2.find(' '));
			this->table_name = str3;
		}
	}*/

	//am ajuns sa scriu singura operatorii, wtf 
	bool operator!()
	{
		if (this->getnb() > -1 && this->getnb() < 10)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void info_coloane()
	{
		bool corect = !*this;
		if (this->getnb() == 0 && corect == 1)
		{
			int ok = 0;
			string str2;
			string define = "CREATE TABLE ";
			size_t position = this->getcmd().find(define);
			str2 = this->getcmd().substr(position + define.length());

			//substrag doar partea de comenzi

			string str3 = str2.substr(str2.find("("), str2.rfind(")"));  //-> rfind e ultima aparitie

			//validare pentru corectitudinea comenzii - partiala
			int nr_coloane = count(str3.begin(), str3.end(), '(');
			int nr_coloane1 = count(str3.begin(), str3.end(), ')');
			if ((nr_coloane + nr_coloane1) % 2 == 0)
			{
				ok = 1;
			}

			if (ok == 0)
			{
				cout << "info_coloane -> Comanda introdusa gresit | greseala formatare ( ) " << endl;
			}

			//mare intrebare
			this->getcmd() = str3;
		}

		else
		{
			cout << "Comanda introdusa gresit | CREATE TABLE SCRIS GRESIT" << endl;
		}
	}


	void define_coloane()
	{
		int ok = 0;
		string c = getcmd();
		c.erase(remove(c.begin(), c.end(), ' '), c.end());
		bool corect = !*this;
		if (this->getnb() == 0 && corect == 1)
		{
			if (this->datas != NULL)
			{
				delete[] datas;
			}
			int nr_coloane = count(c.begin(), c.end(), '(');
			int nr_coloane1 = count(c.begin(), c.end(), ')');
			if ((nr_coloane + nr_coloane1) % 2 == 0)
			{
				ok = 1;
			}

			if (ok == 0)
			{
				cout << endl << "nr_coloane -> Comanda introdusa gresit | vezi restr. coloane" << endl;
			}

			//EXTRAG PARTEA DE COMENZI
			c = c.substr(c.find("(") + 1, c.find_last_of(")"));

			this->size = (nr_coloane + nr_coloane1 - 2) / 2;
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

	void create()
	{
		//this->identificare_comanda();
		//this->info_coloane();
		this->define_coloane();
		if (datas != NULL && getnb() != -1 && getname() != "")
		{
			Table Intance(getname(), size, list_tabele, datas);

		}

		else
			cout << "Comada CREATE TABLE formatata gresit" << endl;
	}

	~comanda_create()
	{
		if (datas != NULL)
		{
			delete[] datas;
		}
	}
};
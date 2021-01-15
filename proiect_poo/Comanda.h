#pragma once
#include <iostream>
#include<string>
#include "Table.h"
//#include "Create.h"

using namespace std;

class comanda
{
private:
	int nr;
	string comanda_introdusa;
	string nume_tabela;

public:

	comanda() : nr(-1), comanda_introdusa(""), nume_tabela("") {}

	comanda(string cmd) : comanda()
	{
		this->comanda_introdusa = cmd;
		this->identificare_comanda();
		this->table_name();
	}

	comanda(const comanda& c)
	{
		this->comanda_introdusa = c.comanda_introdusa;
		this->nr = c.nr;
		this->nume_tabela = c.nume_tabela;
	}

	comanda& operator=(const comanda& c)
	{
		this->comanda_introdusa = c.comanda_introdusa;
		this->nr = c.nr;
		this->nume_tabela = c.nume_tabela;
		return *this;
	}

	string getname()
	{
		return this->nume_tabela;
	}

	int getnb()
	{
		return this->nr;
	}

	string getcmd()
	{
		return this->comanda_introdusa;
	}



	void identificare_comanda()
	{
		const char* commands[10] = { "CREATE TABLE ","DROP TABLE ", "DISPLAY TABLE ", "CREATE INDEX ", "DROP INDEX ", "INSERT INTO ", "DELETE FROM ","SELECT ALL FROM ", "SELECT ", "UPDATE " };
		size_t position = -1;  int ok = 0; int val = -1;

		for (int i = 0; i < 10 && ok == 0; i++)
		{
			string define = (char*)commands[i];
			position = this->comanda_introdusa.find(define);
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

	void table_name()
	{
		if (nr != -1 && comanda_introdusa != "")
		{
			string str2, str3;
			if (nr == 1)
			{
				string cmd = "DROP TABLE ";
				size_t position = comanda_introdusa.find(cmd);
				str2 = comanda_introdusa.substr(position + cmd.length());
				this->nume_tabela = str2;
			}

			if (nr == 0)
			{
				string cmd = "CREATE TABLE ";
				size_t position = comanda_introdusa.find(cmd);
				str2 = comanda_introdusa.substr(position + cmd.length());
				str3 = str2.substr(0, str2.find(' '));
				this->nume_tabela = str3;
			}

			if (nr == 2)
			{
				string cmd = "DISPLAY TABLE ";
				size_t position = comanda_introdusa.find(cmd);
				str2 = comanda_introdusa.substr(position + cmd.length());
				this->nume_tabela = str2;
			}

			if (nr == 5)
			{
				string cmd = "INSERT INTO ";
				size_t position = comanda_introdusa.find(cmd);
				str2 = comanda_introdusa.substr(position + cmd.length());
				str3 = str2.substr(0, str2.find(' '));
				this->nume_tabela = str3;

			}

			if (nr == 6)
			{
				string cmd = "DELETE FROM ";
				size_t position = comanda_introdusa.find(cmd);
				str2 = comanda_introdusa.substr(position + cmd.length());
				str3 = str2.substr(0, str2.find(' '));
				this->nume_tabela = str3;

			}

			if (nr == 7)
			{
				string cmd = "SELECT ALL FROM ";
				size_t position = comanda_introdusa.find(cmd);
				str2 = comanda_introdusa.substr(position + cmd.length());
				str3 = str2.substr(0, str2.find(' '));
				this->nume_tabela = str3;

			}

			if (nr == 8)
			{	//caz SELECT c1, c2 ...
				string cmd = "FROM ";
				size_t position = comanda_introdusa.find(cmd);
				str2 = comanda_introdusa.substr(position + cmd.length());
				str3 = str2.substr(0, str2.find(' '));
				this->nume_tabela = str3;
			}

			if (nr == 9)
			{
				string cmd = "UPDATE ";
				size_t position = comanda_introdusa.find(cmd);
				str2 = comanda_introdusa.substr(position + cmd.length());
				str3 = str2.substr(0, str2.find(' '));
				this->nume_tabela = str3;

			}

		}


		else
		{
			cout << "Comanda introdusa gresit ." << endl;
		}

	}
}; 
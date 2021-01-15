#pragma once
#include <iostream>
#include <string>
#include "Table.h"


using namespace std;

// cine nu are destule probleme,
//                               isi face.

//class Executabil
//{
//public:
//	virtual void identificare_comanda() = 0;
//	virtual void table_name() = 0;
//};

class comanda
{
private:
	int nr = -1;
	string comanda_introdusa;
	string nume_tabela;

public:
	comanda()
	{
		nr = -1;
		comanda_introdusa = "";
		nume_tabela = "";
	}

	comanda(string cmd)
	{
		comanda_introdusa = cmd;
		identificare_comanda();
		table_name();
	}

	virtual void drop(vector <Table>& list_tabele) {}

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
		return comanda_introdusa;
	}

	void setcdm(string s)
	{
		this->comanda_introdusa = s;
	}

	void setnb(int nr)
	{
		this->nr = nr;
	}

	void setname(string name)
	{
		this->nume_tabela = name;
	}

	void identificare_comanda()
	{
		const char* commands[10] = { "CREATE TABLE ","DROP TABLE ", "DISPLAY TABLE ", "CREATE INDEX ", "DROP INDEX ", "INSERT INTO ", "DELETE FROM ","SELECT ALL FROM ", "SELECT ", "UPDATE " };
		size_t position = -1;  int ok = 0; int val = -1;

		for (int i = 0; i < 10 && ok == 0; i++)
		{
			string define = (char*)commands[i];
			position = getcmd().find(define);
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
			cout << "Identificare_comanda -> Comanda introdusa gresit SAU posibilitatea ca in .txt sa fie randuri goale" << endl;
		}

		else
		{
			setnb(val);
		}
	}

	void table_name()
	{
		if (getnb() != -1 && getcmd() != "")
		{
			string str2, str3;
			if (getnb() == 1)
			{
				string cmd = "DROP TABLE ";
				size_t position = getcmd().find(cmd);
				str2 = getcmd().substr(position + cmd.length());
				setname(str2);
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
				str2.erase(remove(str2.begin(), str2.end(), ' '), str2.end());
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
			{
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
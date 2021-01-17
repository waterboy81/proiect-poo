#pragma once
#include <iostream>
#include <string>
#include "Table.h"


using namespace std;

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

	//virtual void drop(vector <Table>& list_tabele){}

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
		const char* commands[12] = { "CREATE TABLE ","DROP TABLE ", "DISPLAY TABLE ", "CREATE INDEX ", "DROP INDEX ", "INSERT INTO ", "DELETE FROM ","SELECT ALL FROM ", "SELECT ", "UPDATE ", "BINARY CREATE ", "IMPORT " };
		size_t position = -1;  int ok = 0; int val = -1;

		for (int i = 0; i < 12 && ok == 0; i++)
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

			if (nr == 10) 
			{
				string cmd = "BINARY CREATE ";
				size_t position = comanda_introdusa.find(cmd);
				str2 = comanda_introdusa.substr(position + cmd.length());
				this->nume_tabela = str2;
			}

			if (getnb() == 11)
			{
				string cmd = "IMPORT ";
				size_t position = getcmd().find(cmd);
				str2 = getcmd().substr(position + cmd.length());
				str3 = str2.substr(0, str2.find(' '));
				setname(str3);
			}
		}

		else
		{
			cout << "Comanda introdusa gresit ." << endl;
		}

	}

};

class comanda_import : public comanda 
{
private:
	string name_csv;
	vector <string> values_imported;
public: 
	comanda_import(string cmd) : comanda(cmd)
	{
		name_csv = n_fisier();
	}

	string n_fisier() 
	{
		string n = getname() + " "; string c = getcmd();
		n = c.substr(c.find(n)+n.length(), c.length());
		n.erase(remove(n.begin(), n.end(), ' '), n.end());
		return n;
	}

	void setvalues(vector<Table>&list) 
	{
		extract(list);
	}

	int corect(vector<Table> list) 
	{
		for (int i = 0; i < list.size(); i++) 
		{
			if (list[i].getNume_tabela() == getname()) 
			{
				return i;
			}
		}

		return -1;
	}

	void extract(vector<Table> list) 
	{
		fstream f(name_csv); string buffer; string to_add;
		int size = corect(list);
		if (f.is_open()&& size!=-1) 
		{
			getline(f, buffer);
			while (!f.eof())
			{
				getline(f, buffer); //full row
				buffer = buffer + ",";
				for (int i = 0; i < list[size].getNr_coloane(); i++) 
				{
					to_add = buffer.substr(0, buffer.find_first_of(","));
					values_imported.push_back(to_add);
					buffer = buffer.substr(buffer.find_first_of(",")+1,buffer.length()-to_add.length()+1);
				}

			}		
		}
	}

	void import(vector <Table> &list) 
	{
		int index = corect(list);
		list[index].set_csv(values_imported);
	}

};

class comanda_binary : public comanda
{
private: 

public:
	comanda_binary(string cmd) : comanda(cmd) {}

	void read(vector<Table> &list) //functioneaza, am testat
	{
		int l = 0; string s=getname();
		ifstream f(s, ios::binary);
		if (f.is_open()) {
			vector <coloana> bb;
			f.read((char*)&l, sizeof(l));
			char* aux = new char[l + 1];
			f.read(aux, l + 1);
			s = aux; //nume tabela
			delete[] aux;

			while (!f.eof()) //eof imi da fail sau e corput binarul , deci serializarea nu a generat un binar bun
			{
				f.read((char*)&l, sizeof(l));
				aux = new char[l + 1];
				f.read(aux, l + 1);
				string nume_c = aux; //nume col
				delete[] aux;

				f.read((char*)&l, sizeof(l));
				aux = new char[l + 1];
				f.read(aux, l + 1);
				string r1 = aux;
				delete[] aux; //type

				int a = 0;
				f.read((char*)&a, sizeof(a));
				int s = a; //size


				f.read((char*)&l, sizeof(l));
				aux = new char[l + 1];
				f.read(aux, l + 1);
				string r2 = aux;
				delete[] aux; //predef

				constraints x(r1, s, r2);
				coloana y(nume_c, x);
				bb.push_back(y);
			}

			Table a(s, bb.size() - 1, list, bb);
			cout << "Table " << a.getNume_tabela() << " created." << endl;
			f.close();
		}
		else
			cout << "Fisierul nu a putut fi deschis." << endl;

	}
};
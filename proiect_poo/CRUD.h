#pragma once
#include <iostream>
#include <string>
#include "Table.h"
#include "Comanda.h"

using namespace std;

class comanda_insert : public comanda
{
private:
	string* values = NULL;
	int size = 0;
public:

	comanda_insert(string c) : comanda(c)
	{
		size = ssize(getcmd());
		setva();
	}

	int getsize()
	{
		return size;
	}

	int ssize(string cmd)
	{
		size = count(cmd.begin(), cmd.end(), ',') + 1;
		return size;
	}

	void setva()
	{
		if (valori(getcmd()) != NULL)
		{
			this->values = new string[this->size];
			for (int i = 0; i < this->size; i++) {
				values[i] = valori(getcmd())[i];
			}
		}

		else
		{
			this->values = NULL;
			this->size = 0;
		}
	}

	string* getvals()
	{
		if (values != nullptr)
		{
			string* copie = new string[size];
			for (int i = 0; i < size; i++)
			{
				copie[i] = values[i];

			}
			return copie;
		}
		else
		{
			return nullptr;
		}
	}


	string* valori(string cmd)
	{
		string cord = "VALUES "; string* vals = NULL;
		int i = 0; string buff; string delimitator = ",";
		string str;

		int position = cmd.find(cord);
		if (position != string::npos)
		{
			vals = new string[size];
			buff = cmd.substr(cmd.find("(") + 1, cmd.find(")") - cmd.find("(") - 1);
			buff = buff + delimitator;
			for (int i = 0; i < size; i++)
			{
				str = buff.substr(0, buff.find(","));
				vals[i] = str;
				buff = buff.substr(buff.find(",") + 1, buff.length() - buff.find(",") + 1);
			}
		}

		if (vals != NULL)
		{
			return vals;
		}
		else
		{
			return NULL;
		}
	}

	void insert(vector<Table>& list)
	{
		if (values != NULL && list.size() > 0)
		{

			for (unsigned int i = 0; i < list.size(); i++)
			{
				if (list[i].getNume_tabela() == getname() && list[i].getNr_coloane() == this->size)
				{
					for (int j = 0; j < list[i].getNr_coloane(); j++)
					{
						list[i].getcol()[j].add_values(values[j], 1);
					}
					cout << "Values successfully added to database in table " << getname() << endl;
				}
			}
		}
		else
			cout << "ERROR: insert_table -> comanda formatata gresit" << endl;


	}


	~comanda_insert() {
		if (values != NULL)
		{
			delete[] values;
		}
	}
};

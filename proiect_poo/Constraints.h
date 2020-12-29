#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Coloana.h"

using namespace std;

class constraints
{
private:

	string type = "";
	string val_predefinita = "";
	int size = 0;

	friend ostream& operator<<(ostream&, constraints);
	friend istream& operator>>(istream& i, constraints c);

public:
	
	constraints() {}

	constraints(string type, string size, string val_predefinita)
	{
		this->type = type;
		this->size = stoi(size); //coversie string->int pentru restrictia size
		this->val_predefinita = val_predefinita;
	}

	constraints(const constraints& r)
	{
		this->type = r.type;
		this->size = r.size;
		this->val_predefinita = r.val_predefinita;
	}

	constraints& operator=(const constraints& r)
	{
		this->type = r.type;
		this->size = r.size;
		this->val_predefinita = r.val_predefinita;

		return *this;
	}

	//metoda type_data pentru insert into
	int type_data(constraints r)
	{
		int ok = 1;
		if (r.type == "INTEGER" || r.type == "INT" || r.type == "INT2")
		{
			return 0;
		}

		if (r.type == "FLOAT" || r.type == "REAL")
		{
			return 1;
		}
		if (r.type == "VARCHAR" || r.type == "TEXT" || r.type == "CHARACTER")
		{
			return 2;
		}

		else
			return -1;
	}
	

	//functii acces

	string getType()
	{
		return type;
	}

	void setType(string type)
	{
		this->type = type;
	}

	string getVal_predefinita()
	{
		return val_predefinita;
	}

	void setVal_predefinita(string val_predefinita)
	{
		this->val_predefinita = val_predefinita;
	}

	int getSize()
	{
		return size;
	}

	void setSize(int size)
	{
		this->size = size;
	}

	
	//supraincarcari operatori

	bool operator!()
	{
		return size > 0;
	}

	constraints operator++()
	{
		this->size++;
		return *this;
	}

	constraints operator++(int i)
	{
		constraints copie = *this;
		this->size++;
		return copie;
	}

	constraints operator+(int valoare)
	{
		constraints copie = *this;
		copie.size += valoare;
		return copie;
	}

	explicit operator int()
	{
		return size;
	}

	int operator()()
	{
		if (type != "")
			return type.size();
		else
			return 0;
	}

	int operator==(constraints& c)
	{
		if (this->type == c.type) return true;
		else return false;
	}

	int operator>=(constraints& c)
	{
		if (this->size >= c.size) return true;
		else return false;
	}


	~constraints() {}

};


ostream& operator<<(ostream& out, constraints r)
{
	cout << endl;
	cout << "RESTRICTII COLOANA " << endl;

	cout << "Tipul de data acceptat-> ";
	out << r.type << " ";
	cout << endl << "Size-> ";
	out << r.size << " ";
	cout << endl << "Valoare default-> ";
	out << r.val_predefinita << " " << endl;

	return out;
}


istream& operator>>(istream& i, constraints c)
{
	i >> c.type;
	i >> c.val_predefinita;
	i >> c.size;
	return i;
}

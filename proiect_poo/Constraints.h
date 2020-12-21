#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Coloana.h"
using namespace std;

class constraints
{
public:

	string type = "";
	string val_predefinita = "";
	int size = 0;

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

	~constraints()
	{

	}

	friend ostream& operator<<(ostream&, constraints);
};

//supraincarcare <<
ostream& operator<<(ostream& out, constraints r)
{
	cout << "RESTRICTII COLOANA= " << endl;
	cout << "Tipul de data acceptat-> ";
	out << r.type << "| ";
	cout << "Size-> ";
	out << r.size << "| ";
	cout << "Valoare default-> ";
	out << r.val_predefinita << " | " << endl;

	return out;
}

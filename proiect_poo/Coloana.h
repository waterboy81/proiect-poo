#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Constraints.h"
using namespace std;

class coloana
{
public:
	//vector <string> data; //->datele config de la consola
	//vector <coloana> coloane;
	string nume;
	constraints restrictii;

	coloana() : restrictii()
	{
		nume = "";

	}

	coloana(string nume, constraints restrictii) : restrictii(restrictii), nume(nume) {}


	coloana(const coloana& c)
	{
		nume = c.nume;
		restrictii = c.restrictii;
	}

	coloana& operator=(const coloana& c)
	{
		nume = c.nume;
		restrictii = c.restrictii;

		return *this;
	}


	~coloana()
	{
	}

	friend ostream& operator<<(ostream&, coloana);
};

ostream& operator<<(ostream& out, coloana c)
{
	cout << "Numele coloanei= ";
	out << c.nume << endl;
	out << c.restrictii;
	return out;
}

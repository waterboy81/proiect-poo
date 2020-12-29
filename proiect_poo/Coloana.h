#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Constraints.h"
using namespace std;

class coloana
{
public:

	string nume;
	constraints restrictii;
	string values[40];
	int nb_values = 0;

	coloana() : restrictii()
	{
		nume = "";


	}

	coloana(string nume, constraints restrictii) : restrictii(restrictii), nume(nume)
	{

	}


	coloana(const coloana& c)
	{
		nume = c.nume;
		restrictii = c.restrictii;
	}

	coloana& operator=(const coloana& c)
	{
		nume = c.nume;
		restrictii = c.restrictii;
		nb_values = c.nb_values;
		for (int i = 0; i < c.nb_values; i++)
		{
			values[i] = c.values[i];
		}

		return *this;
	}

	void add_values(string values_to_add, int values_added) //adauga o valoare pe o coloana/ la fiecare apel
	{
		int k = 0;
		if (values_to_add != "")
		{
			for (int i = 0; i < 40 && k < 1; i++)
			{
				if (values[i] == "" && k < values_added)
				{
					values[i] = values_to_add;
					k++;

				}
			}

		}

		if (k == 0)
		{
			cout << "add_values -> s-a depasit limita de 40 de valori posibile / coloana" << endl;
		}
	}






	~coloana()
	{
	}

	friend ostream& operator<<(ostream&, coloana);

};

ostream& operator<<(ostream& out, coloana c)
{
	cout << "Numele coloanei= ";
	out << c.nume;
	out << c.restrictii;
	return out;
}

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Constraints.h"

using namespace std;

class coloana
{
private:

	string nume;
	constraints restrictii;
	string values[40];
	int nb_values = 0;

	friend ostream& operator<<(ostream&, coloana);
	friend istream& operator>>(istream& in, coloana& c);

public:

	coloana() : restrictii()
	{
		nume = "";
		nb_values = 0;
	}

	coloana(string nume, constraints restrictii) : restrictii(restrictii), nume(nume) {}

	coloana(const coloana& c)
	{
		nume = c.nume;
		restrictii = c.restrictii;
		nb_values = c.nb_values;
		for (int i = 0; i < c.nb_values; i++)
		{
			values[i] = c.values[i];
		}
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
					nb_values++;
				}
			}
		}

		if (k == 0)
		{
			cout << "add_values -> s-a depasit limita de 40 de valori posibile / coloana" << endl;
		}
	}


	//functii acces

	string getNume()
	{
		return nume;
	}

	void setNume(string nume)
	{
		this->nume = nume;
	}

	constraints getRestrictii()
	{
		return restrictii;
	}

	void setRestrictii(constraints restrictii)
	{
		this->restrictii = restrictii;
	}

	string* getValues()
	{
		string* adresa = new string[nb_values];
		adresa = &values[0];
		return adresa;
	}

	void setValues(string values[40])
	{
		for (int i = 0; i < 40; i++)
			this->values[i] = values[i];
	}

	void setValue(string value, int i) 
	{
		this->values[i] = value;
	}

	int getNb_values()
	{
		return nb_values;
	}

	void setNb_values(int nb_values)
	{
		this->nb_values = nb_values;
	}

	//supraincarcari operatori

	bool operator!()
	{
		return nb_values > 0;
	}

	coloana operator++() 
	{
		this->nb_values++;
		return *this;
	}

	coloana operator++(int i)
	{
		coloana copie = *this;
		this->nb_values++;
		return copie;
	}

	coloana operator+(int valoare)
	{
		coloana copie = *this;
		copie.nb_values += valoare;
		return copie;
	}

	explicit operator int()
	{
		return nb_values;
	}

	int operator()()
	{
		if (nume != "")
			return nume.size();
		else 
			return 0;
	}

	int operator==(coloana& c)
	{
		if (this->nb_values == c.nb_values) return true;
		else return false;
	}

	int operator>=(coloana& c)
	{
		if (this->nb_values >= c.nb_values) return true;
		else return false;
	}


	~coloana() {}

};


ostream& operator<<(ostream& out, coloana c)
{
	cout << "Numele coloanei= ";
	out << c.nume;
	out << c.restrictii;
	return out;
}
istream& operator>>(istream& in, coloana& c)
{
	in >> c.nume;
	for (int i = 0; i < 40; i++)
		in >> c.values[i];
	in >> c.restrictii;
	return in;
}



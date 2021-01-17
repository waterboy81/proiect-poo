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

	void WriteBinaryFile(Table t)
	{
		string nume_fisier = t.getNume_tabela() + "_data.bin";
		ofstream f(nume_fisier, ios::out | ios::binary | ios::app);
		int l;
		if (!f.is_open())
			cout << "Nu se poate deschide fisierul " << nume_fisier << endl;
		else
		{
			f.clear();
			l = t.getNume_tabela().length();
			f.write((char*)&l, sizeof(l));
			l = l + 1;
			f.write(t.getNume_tabela().c_str(), l);  //ma rog sa nu faca figuri usigned ul din length

			for (int i = 0; i < t.getNr_coloane(); i++)
			{
				l = t.getcol()[i].getNume().length();
				f.write((char*)&l, sizeof(l));
				l = l + 1;
				f.write(t.getcol()[i].getNume().c_str(), l);

				l = t.getcol()[i].getRestrictii().getType().length();
				f.write((char*)&l, sizeof(l));
				l = l + 1;
				f.write(t.getcol()[i].getRestrictii().getType().c_str(), l);

				l = t.getcol()[i].getRestrictii().getSize();
				f.write((char*)&l, sizeof(l));


				l = t.getcol()[i].getRestrictii().getVal_predefinita().length();
				f.write((char*)&l, sizeof(l));
				l = l + 1;
				f.write(t.getcol()[i].getRestrictii().getVal_predefinita().c_str(), l);
			}

			//f.write((char*)&t, sizeof(Table));
			//nu e optim la deserializare 
		}
		f.close();
	}

	~comanda_insert() {
		if (values != NULL)
		{
			delete[] values;
		}
	}
};

class comanda_delete : public comanda
{
private:
	string n_coloana;
	string value;

public:
	comanda_delete(string cmd) : comanda(cmd)
	{
		string c = nume_coloana(getcmd());
		string v = c_value(getcmd());
		if (c != "-1" && v != "-1")
		{
			n_coloana = c;
			value = v;
		}
		else
		{
			n_coloana = "";
			value = "";
		}
	}

	string getvalue() { return value; }
	string getdelcol() { return n_coloana; }


	string nume_coloana(string comanda)
	{
		string cord = "WHERE "; string nume_coloana = "";
		if (comanda.find(cord) != string::npos)
		{
			comanda = comanda.substr(comanda.find(cord) + cord.length(), comanda.length() - comanda.find(cord));
			comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
			nume_coloana = comanda.substr(0, comanda.find("="));
		}
		if (nume_coloana.length() != comanda.length())
		{
			return nume_coloana;
		}

		else
		{
			cout << "nume_coloana -> comanda nu este formatata bine si nu a putut fi extras numele" << endl;
			return "-1";
		}
	}

	string c_value(string comanda)
	{
		string nume = nume_coloana(comanda);
		if (nume != "-1")
		{
			comanda = comanda.substr(comanda.find("=") + 1, comanda.length() - comanda.find("="));
			comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
			return comanda;
		}

		else
			return "-1";
	}

	void delete_from(vector<Table>& list)
	{
		int ok = 0; int contor = 0;
		for (unsigned int i = 0; i < list.size(); i++)
		{
			if (list[i].getNume_tabela() == this->getname())
			{
				for (int j = 0; j < list[i].getNr_coloane(); j++)
				{
					if (list[i].getcol()[j].getNume() == n_coloana)
					{
						for (int k = 0; k < list[i].getcol()[j].getNb_values(); k++)
						{
							if (list[i].getcol()[j].getValues()[k] == value)
							{
								list[i].modificare_date(k);
								ok = 1;
								k--;
								contor++;
							}
						}
					}
				}
			}
		}

		if (ok == 1)
		{
			cout << "Changes have been applied to table " << getname() << ". " << endl << contor << " row/s deleted. ";
			cout << endl;
		}

		else
		{
			cout << "ERROR -> comanda formatata gresit sau in tabela nu exista inregistrari " << endl;
			cout << "Detalii comanda introdusa -> nume_tabel= " << getname() << " nume_coloana= " << n_coloana << " valoare= " << value << endl;
		}
	}
};

class comanda_update : public comanda
{
private:
	string n_coloana;
	string old_value;
	string new_value;

public:
	comanda_update(string cmd) : comanda(cmd)
	{
		if (verificare() == 1)
		{
			n_coloana = nume_update(getcmd());
			old_value = o_value(getcmd());
			new_value = n_value(getcmd());
		}
	}

	string getcol() { return n_coloana; }

	bool verificare()
	{
		string a, b, c; string valid = " WHERE ";
		a = nume_update(getcmd()); b = o_value(getcmd()); new_value = n_value(getcmd());
		size_t indice = getcmd().find(valid);
		if (a != "-1" && b != "-1" && c != "-1" && indice != string::npos && corect(getcmd()) == 1)
		{
			return true;
		}

		return false;
	}

	bool corect(string comanda)
	{
		string cord = "SET "; string cmd = comanda;
		comanda = comanda.substr(comanda.find(cord) + cord.length(), comanda.find_first_of("=") - (comanda.find(cord) + cord.length()));
		comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
		if (cmd.find_first_of(comanda) != cmd.find_last_of(comanda)) { return true; }
		else { return false; }
	}

	string nume_update(string comanda)
	{
		string cord = "SET "; string cmd = comanda;
		if (comanda.find(cord) != string::npos && count(comanda.begin(), comanda.end(), '=') == 2)
		{
			comanda = comanda.substr(comanda.find(cord) + cord.length(), comanda.find_first_of("=") - (comanda.find(cord) + cord.length()));
			comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
			if (corect(cmd) == 1)
			{
				return comanda;
			}
		}

		return "-1";
	}

	string n_value(string comanda)
	{
		string cord = "WHERE ";
		int position = comanda.find(cord);
		if (position != string::npos)
		{
			comanda = comanda.substr(comanda.find("=") + 1, position - comanda.find("=") - 1);
			comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
			return comanda;
		}
		else
		{
			return "-1";
		}
	}

	string o_value(string comanda)
	{
		comanda = comanda.substr(comanda.rfind("=") + 1, comanda.length() - comanda.rfind("="));
		comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
		return comanda;
	}

	void update(vector <Table>& list_tabele)
	{
		int ok = 0; int contor = 0; int okk = 0; int j = 0;
		if (verificare() == 1) {
			for (unsigned int i = 0; i < list_tabele.size(); i++)
			{
				ok++;
				if (list_tabele[i].getNume_tabela() == getname())
				{
					ok++;
					for (j = 0; j < list_tabele[i].getNr_coloane(); j++)
					{
						okk++;
						if (list_tabele[i].getcol()[j].getNume() == n_coloana)
						{
							okk++;
							for (int k = 0; k < list_tabele[i].getcol()[j].getNb_values(); k++)
							{
								if (list_tabele[i].getcol()[j].getValues()[k] == old_value)
								{
									list_tabele[i].getcol()[j].setValue(new_value, k);
									contor++;
								}
							}
						}
					}
				}
			}
		}

		if (contor != 0)
		{
			cout << endl << "Table " << getname() << " has been altered.";
			cout << endl << contor << " row / rows have been updated. " << endl;
		}

		else
		{
			if (ok == list_tabele.size() && contor == 0) cout << "Tabela: " << getname() << " nu se afla in baza de date" << endl;
			else
			{
				if (okk == j) cout << "Coloana " << n_coloana << " nu exista in tabela " << getname() << " ." << endl;
				else cout << "Nu s-au gasit rezultate pentru valoarea " << old_value << " ." << endl;
			}
		}
	}
};

class comanda_select : public comanda
{
private:
public:
	comanda_select(string cmd) : comanda(cmd) {}
	void select_all(vector<Table>& list_tabele)
	{
		int ok = 0;
		for (unsigned int i = 0; i < list_tabele.size(); i++)
		{
			if (list_tabele[i].getNume_tabela() == getname())
			{
				ok = 1;
				cout << "SELECT ALL returned -> " << endl;
				for (int j = 0; j < list_tabele[i].getNr_coloane(); j++)
				{
					cout << "NUME COLOANA: " << list_tabele[i].getcol()[j].getNume() << endl;
					for (int k = 0; k < list_tabele[i].getcol()[j].getNb_values(); k++)
					{

						cout << list_tabele[i].getcol()[j].getValues()[k] << endl;
					}

					cout << endl;
				}

			}
		}

		if (ok == 1)
		{
			cout << "Values from table " << getname() << " have been displayed" << endl;
		}

		else
		{
			cout << "Tabela: " << getname() << " nu exista in baza de date sau nu exista inregistrari" << endl;
		}
	}
};

class select_part : public comanda_select
{
private:
	string* s_coloane = NULL;
	int nr_select = 0;

public:
	select_part(string cmd) : comanda_select(cmd)
	{
		int nr = n_select(getcmd());
		string* s = coloane_name(getcmd(), nr);
		if (nr != 0 && s != NULL)
		{
			nr_select = nr;
			s_coloane = new string[nr_select];
			for (int i = 0; i < nr; i++)
			{
				s_coloane[i] = s[i];
			}
		}
		else
		{
			nr_select = 0;
			string* s_coloane = NULL;
		}

		delete[] s;
	}

	int n_select(string comanda)
	{
		int contor = 0;
		comanda = comanda.substr(comanda.find(" ") + 1, comanda.find("FROM") - comanda.find(" ") - 1);
		comanda = comanda + ",";
		comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
		while (comanda != "")
		{
			int position = comanda.find(",");
			if (position != string::npos)
			{
				contor++;
				comanda = comanda.substr(position + 1, comanda.length() - position);
			}
		}

		if (contor != 0)
		{
			return contor;
		}

		else
		{
			//cout << "nr_select coloane -> coloanele din comandata SELECT nu sunt bine despartite de virgula" << endl;
			return -1;
		}

	}

	bool exista_coloane(coloana* cols, int nr)
	{
		int ok = 0;
		for (int i = 0; i < nr_select; i++)
		{
			for (int j = 0; j < nr; j++)
			{
				if (s_coloane[i] == cols[j].getNume())
				{
					ok++;
				}
			}
		}
		if (ok == nr_select) { return true; }
		else { return false; }
	}

	string* coloane_name(string comanda, int nr_coloane)
	{
		string delimitator = ",";
		string cord = "FROM ";
		string* nume = NULL;

		int position = comanda.find(cord);
		if (position != string::npos)
		{
			nume = new string[nr_coloane];
			comanda = comanda.substr(comanda.find(" ") + 1, comanda.find("FROM") - comanda.find(" ") - 1);
			comanda = comanda + delimitator;
			comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
			for (int i = 0; i < nr_coloane; i++)
			{
				cord = comanda.substr(0, comanda.find(","));
				nume[i] = cord;
				comanda = comanda.substr(comanda.find(",") + 1, comanda.length() - comanda.find(",") + 1);
			}
		}

		return nume;
	}

	void select(vector <Table>& list_tabele)
	{
		int ok = 0;
		if (s_coloane != NULL)
		{
			for (unsigned int i = 0; i < list_tabele.size(); i++)
			{
				if (list_tabele[i].getNume_tabela() == getname() && exista_coloane(list_tabele[i].getcol(), list_tabele[i].getNr_coloane()) == 1)
				{
					ok = 1;
					cout << "SELECT returned -> " << endl;
					for (int t = 0; t < nr_select; t++)
					{
						for (int j = 0; j < list_tabele[i].getNr_coloane(); j++)
						{
							if (list_tabele[i].getcol()[j].getNume() == s_coloane[t])
							{
								cout << "NUME COLOANA: " << list_tabele[i].getcol()[j].getNume() << endl;
								for (int k = 0; k < list_tabele[i].getcol()[j].getNb_values(); k++)
								{
									cout << list_tabele[i].getcol()[j].getValues()[k] << endl;
								}

								cout << endl;
							}
						}
					}
				}
			}
		}

		if (ok == 1)
		{
			cout << "Values from table " << getname() << " have been desplayed" << endl;
		}

		else
			cout << "SELECT nu a putut identifica comenzile / tabela in baza de date" << endl;
	}

	~select_part()
	{
		if (s_coloane != NULL)
		{
			delete[] s_coloane;
		}
	}

};
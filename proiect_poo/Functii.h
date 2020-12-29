#pragma once
#include <iostream>
#include <string>
#include "Table.h"

using namespace std;


int identificare_comanda(string comanda)
{
	const char* commands[10] = { "CREATE TABLE ","DROP TABLE ", "DISPLAY TABLE ", "CREATE INDEX ", "DROP INDEX ", "INSERT INTO ", "DELETE FROM ","SELECT ALL FROM ", "SELECT ", "UPDATE " };
	size_t position = -1;  int ok = 0; int val = -1;

	for (int i = 0; i < 10 && ok == 0; i++)
	{
		string define = (char*)commands[i];
		position = comanda.find(define);
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
		return -1;
	}

	else
	{
		return val;
	}
}


//identifica numele tabelei in comenzile ce fac referire la numele tabelei
string table_name(string comanda)
{
	int nr = identificare_comanda(comanda);
	if (nr != -1)
	{
		string str2;
		if (nr == 1)
		{
			string cmd = "DROP TABLE ";
			size_t position = comanda.find(cmd);
			str2 = comanda.substr(position + cmd.length());
			return str2;
		}

		if (nr == 0)
		{
			string cmd = "CREATE TABLE ";
			size_t position = comanda.find(cmd);
			str2 = comanda.substr(position + cmd.length());
			string str3 = str2.substr(0, str2.find(' '));
			return str3;
		}

		if (nr == 2)
		{
			string cmd = "DISPLAY TABLE ";
			size_t position = comanda.find(cmd);
			str2 = comanda.substr(position + cmd.length());
			return str2;
		}

		if (nr == 5)
		{
			string cmd = "INSERT INTO ";
			size_t position = comanda.find(cmd);
			str2 = comanda.substr(position + cmd.length());
			string str3 = str2.substr(0, str2.find(' '));
			return str3;

		}

		if (nr == 6)
		{
			string cmd = "DELETE FROM ";
			size_t position = comanda.find(cmd);
			str2 = comanda.substr(position + cmd.length());
			string str3 = str2.substr(0, str2.find(' '));
			return str3;

		}

		if (nr == 7)
		{
			string cmd = "SELECT ALL FROM ";
			size_t position = comanda.find(cmd);
			str2 = comanda.substr(position + cmd.length());
			string str3 = str2.substr(0, str2.find(' '));
			return str3;

		}

		if (nr == 8)
		{	//caz SELECT c1, c2 ...
			string cmd = "FROM ";
			size_t position = comanda.find(cmd);
			str2 = comanda.substr(position + cmd.length());
			string str3 = str2.substr(0, str2.find(' '));
			return str3;
		}

		if (nr == 9)
		{
			string cmd = "UPDATE ";
			size_t position = comanda.find(cmd);
			str2 = comanda.substr(position + cmd.length());
			string str3 = str2.substr(0, str2.find(' '));
			return str3;

		}

		return "-1";
	}


	else
	{
		cout << "table_name -> nu s-a putut identifica numele tabelei" << endl;
		return "-1";
	}

}

//delete white spaces pentru anumite formatari de comanda
void delete_spaces(string& comanda)
{
	comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());

}

//metoda numara coloanele selectate
int nr_select(string comanda) 
{
	int contor = 0;
	comanda = comanda.substr(comanda.find(" ") + 1, comanda.find("FROM") - comanda.find(" ") - 1);
	comanda = comanda + ",";
	delete_spaces(comanda);
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
		cout << "nr_select coloane -> coloanele din comandata SELECT nu sunt bine despartite de virgula" << endl;
		return -1;
	}

}

//metoda care segmenteaza si da coloanele care se doresc din select 

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
		delete_spaces(comanda);
		for (int i = 0; i < nr_coloane; i++)
		{
			cord = comanda.substr(0, comanda.find(","));
			nume[i] = cord;
			comanda = comanda.substr(comanda.find(",") + 1, comanda.length() - comanda.find(",") + 1);
		}
	}

	return nume;

}

//metoda care segmenteaza comanda (caz create)

string info_coloane(string comanda)
{
	if (identificare_comanda(comanda) == 0)
	{
		int ok = 0;
		string str2;
		string cmd = "CREATE TABLE ";
		size_t position = comanda.find(cmd);
		str2 = comanda.substr(position + cmd.length());

		//substrag doar partea de comenzi

		string str3 = str2.substr(str2.find("("), str2.rfind(")"));  //-> rfind e ultima aparitie

		//validare pentru corectitudinea comenzii - partiala
		int nr_coloane = count(str3.begin(), str3.end(), '(');
		int nr_coloane1 = count(str3.begin(), str3.end(), ')');
		if ((nr_coloane + nr_coloane1) % 2 == 0)
		{
			ok = 1;
		}

		if (ok == 0)
		{
			cout << "info_coloane -> Comanda introdusa gresit | greseala formatare ( ) " << endl;
		}

		return str3;
	}

	else
	{
		cout << "info_coloane -> Comanda introdusa gresit | CREATE TABLE SCRIS GRESIT" << endl;
		return "-1";
	}
}

//METODA PENTRU CREATE TABLE -> NUMAR COLOANE CREATE

int nr_coloane(string comanda)
{
	if (identificare_comanda(comanda) == 0)
	{
		int ok = 0;
		string str2;
		string cmd = "CREATE TABLE ";
		size_t position = comanda.find(cmd);
		str2 = comanda.substr(position + cmd.length());
		//substrag doar partea de comenzi

		string str3 = str2.substr(str2.find("("), str2.rfind(")"));  //-> rfind e ultima aparitie

		//validare pentru corectitudinea comenzii - partiala
		int nr_coloane = count(str3.begin(), str3.end(), '(');
		int nr_coloane1 = count(str3.begin(), str3.end(), ')');
		if ((nr_coloane + nr_coloane1) % 2 == 0)
		{
			ok = 1;
		}

		if (ok == 0)
		{
			cout << endl << "nr_coloane -> Comanda introdusa gresit | vezi restr. coloane" << endl;
		}

		return (nr_coloane + nr_coloane1 - 2) / 2;
	}

	else
		throw exception("nr_coloane -> Comanda introdusa gresit | vezi restr. coloane");
}



vector <string> data_coloane(string comanda, int nr_coloane)
{   //implementat pe separator "," fara spatii, trebuie o metoda delete spatii goale intre atribute

	vector <string> data;
	string delimitator = ",";
	string cmd = comanda.substr(comanda.find("(") + 1, comanda.rfind(")") - 1);

	for (int i = 0; i < nr_coloane; i++) //imi pare rau ca nu stiu sa implementez delimitator :(
	{									 // it work's tho, pe cate coloane vrei :D	
		string coloana = cmd.substr(cmd.find("(") + 1, cmd.find(")"));
		int size = coloana.length();

		string s = coloana.substr(0, coloana.find(","));
		data.push_back(s);

		coloana = coloana.substr(coloana.find(",") + 1, coloana.find(")"));
		s = coloana.substr(0, coloana.find(","));
		data.push_back(s);

		coloana = coloana.substr(coloana.find(",") + 1, coloana.find(")"));
		s = coloana.substr(0, coloana.find(","));
		data.push_back(s);

		coloana = coloana.substr(coloana.find(","), coloana.find(")"));
		s = coloana.substr(coloana.find(",") + 1, coloana.find(")") - 1);
		data.push_back(s);

		//cmd= cmd.substr(cmd.find("),") + 2, cmd.find("),"));
		cmd.erase(0, size + 1);
	}

	return data;

}


vector <coloana> coloane_tabela(string comanda, int nr, vector <string> data)
{

	//int ok = 1;
	if (identificare_comanda(comanda) == 0 && data.size() > 0 && nr > 1)
	{
		//coloana* coloane_tabela = new coloana[nr]; -> imposibil sa pot salva pointeri la coloane
													//adresa se distruge la a doua interatie
													//din cauza op. = . hmmmmmmmm

		vector <coloana> coloane;
		int i = 0; int j = 0;
		int max_interval = nr * 4 - 1;
		for (j = 0; j <= max_interval; j = j + 4)
		{
			constraints restrictii(data[j + 1], data[j + 2], data[j + 3]);
			coloana c(data[j], restrictii);
			coloane.push_back(c);

		}

		return coloane;
	}

	else
		throw exception("coloane_tabela -> comanda este scrisa gresit sau prea putine coloane adaugate in tabela");
}

//functie ce scoate valori din comanda pentru INSERT INTO
string* valori(string comanda, int nr_coloane)
{
	string cord = "VALUES "; string* nume = NULL;
	int i = 0; string delimitator = ",";
	string str;
	int position = comanda.find(cord);
	if (position != string::npos)
	{
		nume = new string[nr_coloane];
		comanda = comanda.substr(comanda.find("(") + 1, comanda.find(")") - comanda.find("(") - 1);
		comanda = comanda + delimitator;
		for (int i = 0; i < nr_coloane; i++)
		{
			str = comanda.substr(0, comanda.find(","));
			nume[i] = str;
			comanda = comanda.substr(comanda.find(",") + 1, comanda.length() - comanda.find(",") + 1);
		}

	}
	return nume;

}


//metoda pentru delete_from care verifica corectitudineaa comenzii + numele coloanei
string nume_coloana(string comanda)
{
	string cord = "WHERE "; string nume_coloana = "";
	if (comanda.find(cord) != string::npos)
	{
		comanda = comanda.substr(comanda.find(cord) + cord.length(), comanda.length() - comanda.find(cord));
		delete_spaces(comanda);
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


//return value for delete pe coloana
string value(string comanda)
{
	string nume = nume_coloana(comanda);
	if (nume != "-1")
	{
		comanda = comanda.substr(comanda.find("=") + 1, comanda.length() - comanda.find("="));
		delete_spaces(comanda);
		return comanda;
	}

	else
		cout << "value -> valorea nu a putut fi extrasa" << endl;
	return "-1";

}

//nume coloana pentru update 

string nume_update(string comanda) 
{
	string cord = "SET ";
	comanda = comanda.substr(comanda.find(cord) + cord.length(), comanda.find_first_of("=") - (comanda.find(cord) + cord.length()));
	delete_spaces(comanda);
	return comanda;
}

string new_value(string comanda) 
{
	string cord = "WHERE ";
	int position = comanda.find(cord);
	if (position != string::npos) 
	{
		comanda = comanda.substr(comanda.find("=") + 1, position - comanda.find("=")-1);
		delete_spaces(comanda);
		return comanda;
	}
	else 
	{	
		cout << "new_value -> comanda nu este formatata bine, clauza WHERE trebuie separata cel putin printr-un spatiu"<<endl;
		return "-1";
	}
}

string old_value(string comanda) 
{
	comanda = comanda.substr(comanda.rfind("=")+1, comanda.length() - comanda.rfind("="));
	delete_spaces(comanda);
	return comanda;
}






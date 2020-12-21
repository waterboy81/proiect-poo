#pragma once
#include <iostream>
#include <string>
#include <string>
#include "Table.h"

using namespace std;


int identificare_comanda(string comanda)
{
	size_t position = -1; string str2; int ok = 0; int val = 0;
	const char* commands[7] = { "CREATE TABLE ","DROP TABLE ", "DISPLAY TABLE ", "INSERT INTO ", "SELECT ", "UPDATE ", "DELETE FROM" };

	for (int i = 0; i < 7; i++)
	{
		string define = (char*)commands[i];
		position = comanda.find(define);
		str2 = "";
		if (position != 0 && ok == 0)
		{
			ok = 0;
		}
		else
		{
			ok = 1;
		}

		val = val + (1 - ok);
	}

	if (ok == 0)
	{
		throw exception("identifica_comanda -> Comanda introdusa gresit");
	}

	else
	{
		return val;
	}
}


//identifica numele tabelei in comenzile ce fac referire la numele tabelei
string table_name(string comanda)
{
	string str2;
	if (identificare_comanda(comanda) == 1)
	{
		string cmd = "DROP TABLE ";
		size_t position = comanda.find(cmd);
		str2 = comanda.substr(position + cmd.length());
		return str2;
	}

	if (identificare_comanda(comanda) == 0)
	{
		string cmd = "CREATE TABLE ";
		size_t position = comanda.find(cmd);
		str2 = comanda.substr(position + cmd.length());
		string str3 = str2.substr(0, str2.find(' '));
		return str3;
	}

	if (identificare_comanda(comanda) == 2)
	{
		string cmd = "DISPLAY TABLE ";
		size_t position = comanda.find(cmd);
		str2 = comanda.substr(position + cmd.length());
		return str2;
	}

	else
		throw exception("table_name -> nu s-a putut identifica numele tabelei");

	//DELETE FROM =6
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
			throw exception("info_coloane -> Comanda introdusa gresit");
		}

		return str3;
	}

	else
		throw exception("info_coloane -> Comanda introdusa gresit");
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
			throw exception("nr_coloane -> Comanda introdusa gresit | vezi restr. coloane");
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
													//din cauza op. = . 

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




#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Comanda.h"
#include "Create.h"
#include "Drop.h"
#include "CRUD.h"

using namespace std;


vector <Table> list_tabele;
void display_list(vector <Table> list_tabele)
{
	cout << "Tabele din baza de date sunt: " << endl;

	for (size_t i = 0; i < list_tabele.size(); i++)
	{

		cout << i << " ." << list_tabele[i].getNume_tabela() << " " << endl;
	}

	cout << endl;
}


int main(int argc, char* argv[])
{
	ifstream ff;
	//argv[argc]
	ff.open("Comenzi_consola.txt");
	string c;
	if (ff.is_open()) {
		while (getline(ff, c))
		{
			comanda cmd(c);

			if (cmd.getnb() == 0)
			{
				comanda_create e(c);
				e.create(list_tabele);

			}
			if (cmd.getnb() == 1)
			{
				drop_table e(c);
				e.drop(list_tabele);
			}
			if (cmd.getnb() == 2)
			{
				drop_table e(c);
				e.display_table(list_tabele);
			}
			if (cmd.getnb() == 5)
			{
				comanda_insert e(c);
				e.insert(list_tabele);
			}
			if (cmd.getnb() == 6)
			{
				comanda_delete e(c);
				e.delete_from(list_tabele);
			}
			if (cmd.getnb() == 7)
			{
				comanda_select e(c);
				e.select_all(list_tabele);
			}
			if (cmd.getnb() == 8)
			{
				select_part e(c);
				e.select(list_tabele);
			}
			if (cmd.getnb() == 9)
			{
				comanda_update e(c);
				if (e.verificare() == 0)
				{
					cout << "Comanda formatata gresit" << endl << "=== | " << e.getcmd() << " | ===" << endl;
				}
				else
				{
					e.update(list_tabele);
				}
			}

			if (cmd.getnb() == 10)
			{
				comanda_binary e(c);
				e.read(list_tabele);
			}

			if (cmd.getnb() == 11)
			{
				comanda_import e(c);
				e.setvalues(list_tabele);
				e.import(list_tabele);
			}
		}
	}
	else { cout << "Nu s-a putut deschide fisierul." << endl; }
	ff.close();
	
	display_list(list_tabele);

	//mod de lucru command line

	/*cout << "Introdu comanda " << endl;
	while (getline(cin, c) && c != "EXIT") 
	{
		{
			comanda cmd(c);

			if (cmd.getnb() == 0)
			{
				comanda_create e(c);
				e.create(list_tabele);

			}
			if (cmd.getnb() == 1)
			{
				drop_table e(c);
				e.drop(list_tabele);
			}
			if (cmd.getnb() == 2)
			{
				drop_table e(c);
				e.display_table(list_tabele);
			}
			if (cmd.getnb() == 5)
			{
				comanda_insert e(c);
				e.insert(list_tabele);
			}
			if (cmd.getnb() == 6)
			{
				comanda_delete e(c);
				e.delete_from(list_tabele);
			}
			if (cmd.getnb() == 7)
			{
				comanda_select e(c);
				e.select_all(list_tabele);
			}
			if (cmd.getnb() == 8)
			{
				select_part e(c);
				e.select(list_tabele);
			}
			if (cmd.getnb() == 9)
			{
				comanda_update e(c);
				if (e.verificare() == 0)
				{
					cout << "Comanda formatata gresit" << endl << "=== | " << e.getcmd() << " | ===" << endl;
				}
				else
				{
					e.update(list_tabele);
				}
			}

			if (cmd.getnb() == 10)
			{
				comanda_binary e(c);
				e.read(list_tabele);
			}
		}
	}*/

	//testatre derivare, instantiaza bine. mai trebuie impuse verificari. instantiere prin metoda din derivata
	//comanda trebuie derivata pentru tipurile select, update, insert si delete. (4 clase noi) :D

}
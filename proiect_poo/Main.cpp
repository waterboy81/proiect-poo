#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Comanda.h"
#include "Create.h"
#include "Drop.h"
#include "CRUD.h"
//#include "Comenzi_SGBD.h"


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
	string c;
	while (getline(cin, c) && c != "EXIT")
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

	}


	//testatre derivare, instantiaza bine. mai trebuie impuse verificari. instantiere prin metoda din derivata
	//comanda trebuie derivata pentru tipurile select, update, insert si delete. (4 clase noi) :D

	//getline(cin, c);
	//comanda_create b (c);
	//b.create(list_tabele);
	//b.drop(list_tabele);
	//display_list(list_tabele);


	//ifstream c;
	//c.open("Comenzi_consola.txt");
	//while (getline(c, comanda))
	//{
	//	int cod = identificare_comanda(comanda);
	//	if (cod == 0)
	//		create_table(comanda, lista_tabele);
	//	if (cod == 1)
	//		drop_table(comanda, lista_tabele);
	//	if (cod == 2)
	//		display_table(comanda, lista_tabele);
	//	/*if (cod == 3)
	//		create_index(comanda);
	//	if (cod == 4)
	//		drop_index(comanda);*/
	//	if (cod == 5)
	//		insert_into(comanda);
	//	if (cod == 6)
	//		delete_from(comanda);
	//	if (cod == 7)
	//		select_all(comanda);
	//	if (cod == 8)
	//		select(comanda);
	//	if (cod == 9)
	//		update(comanda);
	//}

	//c.close();

}

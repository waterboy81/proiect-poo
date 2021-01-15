#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Comenzi_SGBD.h"
#include "Comanda.h"
#include "Create.h"

using namespace std;

int main(int argc, char* argv[])
{
	string c;  getline(cin, c);
	comanda a(c);

	cout << a.getname() << endl;
	cout << a.getnb() << endl;
	cout << a.getcmd() << endl;

	//testatre derivare, instantiaza bine. mai trebuie impuse verificari. instantiere prin metoda din derivata
	//comanda trebuie derivata pentru tipurile select, update, insert si delete. (4 clase noi) :D

	getline(cin, c);
	comanda_create b(c);
	b.create();

	display_list();

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

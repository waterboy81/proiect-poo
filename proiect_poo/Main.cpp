#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Comenzi_SGBD.h"

using namespace std;

int main()
{
	string comanda;
	ifstream c;
	c.open("Comenzi_consola.txt");
	while (getline(c, comanda))
	{
		int cod = identificare_comanda(comanda);
		if (cod == 0)
			create_table(comanda, lista_tabele);
		if (cod == 1)
			drop_table(comanda, lista_tabele);
		if (cod == 2)
			display_table(comanda, lista_tabele);
		/*if (cod == 3)
			create_index(comanda);
		if (cod == 4)
			drop_index(comanda);*/
		if (cod == 5)
			insert_into(comanda);
		if (cod == 6)
			delete_from(comanda);
		if (cod == 7)
			select_all(comanda);
		if (cod == 8)
			select(comanda);
		if (cod == 9)
			update(comanda);
	}

	c.close();


}

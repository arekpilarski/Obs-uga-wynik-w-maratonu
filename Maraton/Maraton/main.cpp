#include <iostream>
#include <string>
#include <fstream>
#include "funkcje.h"
#include "ZwolnijPamiec.h"



int main(int argc, char** argv)
{
	ifstream plik;
	string Nazwisko, czas, Data, tytul;
	ofstream zapis;
	Zawodnicy* korzen = nullptr;
	Maratony*  glowa  = nullptr;
	string*    pliki  = nullptr;
	PobierzPliki(pliki, argc, argv);
	for (int i = 0; i < argc - 2; i++)
		TworzenieStruktury(Nazwisko, czas, Data, tytul, plik, pliki[i], korzen, glowa);
	TworzPliki(glowa, zapis, korzen);
	ZwolnijPamiec(korzen, glowa);
}


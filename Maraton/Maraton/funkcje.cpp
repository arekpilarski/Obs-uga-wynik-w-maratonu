#include <iostream>
#include <string>
#include <fstream>
#include "funkcje.h"


//-----------------------------------------------------------------------------------------------

void pomoc()
{
	cout << "Podaj pliki wejsciowe w nastepujacy sposob: " << endl;
	cout << "Maraton.exe -i nazwa_pliku1.txt nazwa_pliku2.txt nazwa_pliku3.txt" << endl;
	cout << "Liczba plikow wejsciowych nie jest ograniczona." << endl;
	exit(0);
}

//-----------------------------------------------------------------------------------------------

void OtworzPlik(const string &nazwa_pliku, ifstream &plik)
{
	plik.open(nazwa_pliku, ios::in);
	if (!plik.good())
	{
		cout << "Plik nie zostal otworzony poprawnie." << endl;
		pomoc();
	}
}

//-----------------------------------------------------------------------------------------------

void DodajDoListaMaratonow(ifstream &plik, Maratony* &glowa, string &data, string &tytul, string &Data, Maratony *&Maraton)
{
	getline(plik, tytul);
	getline(plik, Data);
	if (!glowa || glowa->data > Data)
	{
		glowa = new Maratony{ tytul, data, glowa };
		Maraton = glowa;
	}
	else
	{
		Maratony * detektor = glowa;
		while (detektor->next && detektor->next->data < Data)
		{
			detektor = detektor->next;
		}
		detektor->next = new Maratony{ tytul, Data,detektor->next };
		Maraton = detektor->next;
	}
}

//-----------------------------------------------------------------------------------------------

void DodajCzas(Zawodnicy* &korzen, Maratony * &Maraton, string &Data, string &czas)
{
	if (korzen->Czas_zawodnika->Zawody->data > Data)
	{
		korzen->Czas_zawodnika = new Czas{ czas, korzen->Czas_zawodnika, Maraton };

	}
	else
	{
		Czas * segregator = korzen->Czas_zawodnika;
		while (segregator->next && Data > segregator->next->Zawody->data)
		{
			segregator = segregator->next;
		}
		segregator->next = new Czas{ czas, segregator->next, Maraton };
	}
}

//-----------------------------------------------------------------------------------------------

void Iteracyjnie(Zawodnicy* &korzen, string &Nazwisko, Czas* Time, Maratony* &Maraton, string &czas, string &Data)
{
	if (!korzen)
	{
		Time = new Czas{ czas, nullptr, Maraton };
		korzen = new Zawodnicy{ Nazwisko, nullptr, nullptr, Time };
	}
	 else
	{
		Zawodnicy* tmp_korzen = korzen;
		while (tmp_korzen)
		{
			if (Nazwisko >= tmp_korzen->Nazwisko) 
			{
				if (Nazwisko == tmp_korzen->Nazwisko)
				{
					DodajCzas(tmp_korzen, Maraton, Data, czas);
					break;
				}
				if (!tmp_korzen->prawy)
				{
					Time = new Czas{ czas, nullptr, Maraton };
					tmp_korzen->prawy = new Zawodnicy{ Nazwisko, nullptr, nullptr, Time };
					break;
				}
				else
				{
					tmp_korzen = tmp_korzen->prawy;
				}
			}
			else
			{
				if (!tmp_korzen->lewy)
				{
					Time = new Czas{ czas, nullptr, Maraton };
					tmp_korzen->lewy = new Zawodnicy{ Nazwisko, nullptr, nullptr, Time };
					break;
				}
				else {
					tmp_korzen = tmp_korzen->lewy;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------

void DodajDoDrzewaZawodnikow(ifstream &plik, Zawodnicy* &korzen, string &Nazwisko, string &czas, Maratony* &Maraton, string &Data)
{
	string  pomoc;   // pomoc - zbiera niepotrzebne dane.
	plik >> pomoc >> Nazwisko >> pomoc >> czas;
	Nazwisko.erase(Nazwisko.end() - 1);
	Czas * Time = nullptr;
	Iteracyjnie(korzen, Nazwisko, Time, Maraton, czas, Data);

}

//-----------------------------------------------------------------------------------------------

void TworzenieStruktury(string &Nazwisko, string &czas, string &Data, string &tytul, ifstream &plik, string &nazwa_pliku, Zawodnicy* &korzen, Maratony* &glowa)
{
	Maratony * Maraton = nullptr;
	OtworzPlik(nazwa_pliku, plik);
	DodajDoListaMaratonow(plik, glowa, Data, tytul, Data, Maraton);
	while (plik.good())
		DodajDoDrzewaZawodnikow(plik, korzen, Nazwisko, czas, Maraton, Data);
	plik.close();
}

//-----------------------------------------------------------------------------------------------

void PobierzPliki(string* &pliki, int argc, char** argv)
{
	if (argc < 3)
	{
		pomoc();
	}
	if (argv[1][0] == '-')
	{
		if (argv[1][1] == 'i')
		{
			pliki = new string[argc - 2];
			for (int i = 0; i < argc - 2; i++)
			{
				pliki[i] = argv[i + 2];
			}
		}
		else if (argv[1][1] == 'h')
		{
			pomoc();
		}
		else
		{
			cout << "Blednie wprowadzone dane." << endl;
			pomoc();
		}
	}
	else
	{
		cout << "Blednie wprowadzone dane." << endl;
		pomoc();
	}

}

//-----------------------------------------------------------------------------------------------

int Dlugosc(Maratony * &glowa)
{
	int max = 0;
	Maratony * dlugosc = glowa;
	while (dlugosc)
	{
		if (size(dlugosc->nazwa_maratonu) > max)
			max = size(dlugosc->nazwa_maratonu);
		dlugosc = dlugosc->next;
	}
	return max;
}

//-----------------------------------------------------------------------------------------------

void TworzPliki(Maratony * &glowa, ofstream &zapis, Zawodnicy* &root)
{
	if (!root) return;
	TworzPliki(glowa, zapis, root->lewy);
	root->Nazwisko.append(".txt");
	zapis.open(root->Nazwisko, ios::out);
	for (int i = 0; i < 4; i++)
		root->Nazwisko.erase(root->Nazwisko.end() - 1);
	zapis << root->Nazwisko << endl << endl;
	Zawodnicy * wypisz = root;
	while (wypisz->Czas_zawodnika)
	{
		zapis << root->Czas_zawodnika->Zawody->data << " " << root->Czas_zawodnika->Zawody->nazwa_maratonu;
		int spacje = Dlugosc(glowa) - size(root->Czas_zawodnika->Zawody->nazwa_maratonu);
		for (int i = 0; i < spacje+1; i++)
			zapis << " "; 
		zapis << root->Czas_zawodnika->time << endl;
		wypisz->Czas_zawodnika = wypisz->Czas_zawodnika->next;
	}
	zapis.close();
	TworzPliki(glowa, zapis, root->prawy);
}

//-----------------------------------------------------------------------------------------------

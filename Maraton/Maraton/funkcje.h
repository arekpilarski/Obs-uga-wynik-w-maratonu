#pragma once
#include <string>
#include <fstream>
using namespace std;

struct Maratony
{
	string nazwa_maratonu;
	string data;
	Maratony * next;
};

struct Czas
{
	string time;
	Czas* next;
	Maratony* Zawody;

};

struct Zawodnicy
{
	string Nazwisko;
	Zawodnicy* lewy;
	Zawodnicy* prawy;
	Czas* Czas_zawodnika;
};

void OtworzPlik(const string &nazwa_pliku, ifstream &plik);
void DodajDoListaMaratonow(ifstream &plik, Maratony* &glowa, string &data, string &tytul, string &Data, Maratony *&Maraton);
void DodajCzas(Zawodnicy* &korzen, Maratony * &Maraton, string &Data, string &czas);
void Iteracyjnie(Zawodnicy* &korzen, string &Nazwisko, Czas* Time, Maratony* &Maraton, string &czas, string &Data);
void DodajDoDrzewaZawodnikow(ifstream &plik, Zawodnicy* &korzen, string &Nazwisko, string &czas, Maratony* &Maraton, string &Data);
void TworzenieStruktury(string &Nazwisko, string &czas, string &Data, string &tytul, ifstream &plik, string &nazwa_pliku, Zawodnicy* &korzen, Maratony* &glowa);
void PobierzPliki(string* &pliki, int argc, char** argv);
void TworzPliki(Maratony* &glowa, ofstream &zapis, Zawodnicy* &root);
int Dlugosc(Maratony * &glowa);
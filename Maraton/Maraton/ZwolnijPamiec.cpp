#include "funkcje.h"
#include "ZwolnijPamiec.h"


void UsunDrzewoZCzasami(Zawodnicy* &root)
{
	if (!root)
	{
		UsunDrzewoZCzasami(root->lewy);
		UsunDrzewoZCzasami(root->prawy);
		while (root->Czas_zawodnika)
		{
			Czas* tmp_h = root->Czas_zawodnika;
			root->Czas_zawodnika = root->Czas_zawodnika->next;
			delete tmp_h;
		}
		delete root;
		root = nullptr;
	}
}

void UsunListeMaratonow(Maratony * &glowa)
{
	while (glowa)
	{
		Maratony* tmp_h = glowa;
		glowa = glowa->next;
		delete tmp_h;
	}
}

void ZwolnijPamiec(Zawodnicy* &korzen, Maratony* &glowa)
{
	UsunDrzewoZCzasami(korzen);
	UsunListeMaratonow(glowa);
}
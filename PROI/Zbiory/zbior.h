//Projekt nr 2: klasa reprezentujaca zbior macierzy 3x3 typu float
//Przygotowal: Tomasz Bochenski

#ifndef ZBIOR_H_
#define ZBIOR_H_
#include "macierze_szablon.h"

class zbior
{
private:
	//struktura w oparciu o ktora powstanie lista, ktora skladac sie bedzie z elementow zbioru (macierzy)
	struct element
	{
		Macierze_3x3<float> macierz_float;
		element *nastepny;
	};
	//wskaznik na poczatek listy
	element *poczatek;
	//zmienna statyczna przetrzymujaca aktualna liczbe obiektow klasy zbior
	static int ilosc_obiektow;
	//funkcja sprawdzajaca czy podana macierz istnieje (zwraca true) czy nie istnieje (zwraca false)
	bool czy_istnieje(const Macierze_3x3<float> &macierz)const;
	//zmienna przetrzymujaca aktualna liczbe elementow zbioru
	int liczba_elementow_zbioru;
public:
	//konstruktor domyslny
	zbior();
	//konstruktor kopiujacy
	zbior(const zbior &obiekt);
	//destruktor
	~zbior();
	//funcja dodajaca element do zbioru bez sprawdzania czy podany element juz istnieje
	void dodaj_element_bezwarunkowo(const Macierze_3x3<float> &macierz);
	//funckaj dodajaca element do zbioru tylko w przypadku gdy nie ma go jeszcze w zbiorze
	void dodaj_element_warunkowo(const Macierze_3x3<float> &macierz);
	//funkcja usuwajaca element zbioru o podanym numerze
	void usun_element(int numer_macierzy);
	//przeciazenie operatora =
	zbior & operator=(const zbior &obiekt);
	//przeciazenie operatora == (porownania zbiorow)
	bool operator==(const zbior &obiekt)const;
	//przeciazenie operatora != (porownania zbiorow)
	bool operator!=(const zbior &obiekt)const;
	//przeciazenie operatora + (suma zbiorow)
	zbior operator+(const zbior &obiekt)const;
	//przeciazenie operatora * (iloczyn zbiorow)
	zbior operator*(const zbior &obiekt)const;
	//przeciazenie operatora << (drukowanie zawartosci)
	friend ostream & operator << (ostream &wyjscie, const zbior &obiekt);
	//funkcja statyczna zwracajaca liczbe obiektow klasy zbior
	static int zwroc_liczbe_obiektow(void) { return ilosc_obiektow; };
};

#endif


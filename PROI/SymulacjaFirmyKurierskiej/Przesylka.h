//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#ifndef PRZESYLKA_H
#define PRZESYLKA_H
#include "Klient.h"

class Przesylka
{
private:
	Klient p_odbiorca_przesylki;
	int numer_ID_przesylki;
public:
	Przesylka();
	Przesylka(const Klient &odbiorca);
	~Przesylka(void);
	void wyswietl_dane(void);
	Klient zwroc_odbiorce(void) {return p_odbiorca_przesylki;};
};

#endif
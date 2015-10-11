//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#ifndef ODDZIAL_H
#define ODDZIAL_H
#include "Placowka.h"

//w klasie tej nie jest zdefiniowany konstruktor kopiujacy co jest celowym zabiegiem
//podany program nie wykorzystuje konstruktora kopiujacego do dzialania
class Oddzial: public Placowka
{
private:
	std::queue<Przesylka> kolejka_przesylek;
public:
	Oddzial(void);
	Oddzial(std::string lokalizacja_oddz);
	~Oddzial(void);
	void przyjmij_przesylki(void);
	void zaladuj_samochod(void);
	std::string zwroc_lokalizacje(void) {return p_lokalizacja;};
	void rozwoz_przesylki_z_oddzialu(void);
	unsigned wyswietl_liczbe_przesylek(void) {return kolejka_przesylek.size();};
};

#endif
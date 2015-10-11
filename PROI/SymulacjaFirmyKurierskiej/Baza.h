//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#ifndef BAZA_H
#define BAZA_H
#include "Placowka.h"

class Baza: public Placowka
{
private:
	std::vector<Klient> b_baza_klientow;
	std::vector<Przesylka> b_przesylki_w_bazie;
public:
	Baza(void);
	Baza(std::string lokalizacja);
	~Baza(void);
	void dodaj_klienta(std::string tab_klient[4]);
	void usun_klienta(std::string tab_klient[4]);
	void wyswietl_klientow(void);
	void generuj_przesylki(void);
	int zwroc_liczbe_przesylek(void) {return b_przesylki_w_bazie.size();};
	void zaladuj_samochod(void);
	void wyladuj_samochod(int numer);
	void wroc_do_bazy(int numer);
	int liczba_klientow(void) {return b_baza_klientow.size();};
	void rozwoz_przesylki_z_bazy(void);
	void usun_nieaktualnych_klientow(void);
};

#endif
//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#ifndef PLACOWKA_H
#define PLACOWKA_H
#include "Samochod.h"

//struktura elementu tymczasowa przestrzen
//sklada sie z wektora i lokalizacji
//przekazywanie przesylek z bazy do oddzialow odbywac sie bedzie wlasnie za pomoca elementow tymczasowa_przestrzen
struct tymczasowa_przestrzen
{
	std::string lokalizacja;
	std::vector<Przesylka> tmp_przestrzen;
};

//w klasie tej nie jest zdefiniowany konstruktor kopiujacy co jest celowym zabiegiem
//podany program nie wykorzystuje konstruktora kopiujacego do dzialania
class Placowka
{
protected:
	std::string p_typ_placowki;
	std::string p_lokalizacja;
	int ilosc_Ford_Transist_oczekujacych;
	int ilosc_Renault_Master_oczekujacych;
	int ilosc_Volkswagen_Caddy_oczekujacych;
	//kolejka i wektor trzymajace wskazniki na wszystkie mozliwe typy samochodow
	std::queue<Samochod*> p_kolejka_samochodow_oczekujacych;
	std::vector<Samochod*> p_vektor_samochodow_podrozujacych;
public:
	Placowka(void);
	Placowka(std::string typ_placowki, std::string lokalizacja);
	virtual ~Placowka(void);
	void informacje_o_placowce(void);
	void dodaj_samochod(void);
	void usun_samochod(void);
	void wyswietl_stan_samochodow(void);
	int znajdz_przestrzen(std::string lokalizacja);	  //zwraca indeks pod ktorym jest szukana przestrzen
	void wroc_do_placowki(int numer);
};

#endif

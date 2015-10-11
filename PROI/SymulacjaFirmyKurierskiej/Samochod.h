//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#ifndef SAMOCHOD_H
#define SAMOCHOD_H
#include "Przesylka.h"

//klasa bazowa, po ktorej dziedziczyc beda trzy inne klasy reprezentujace rozne typy samochodow
class Samochod
{
private:
	int s_numer_ID_pojazdu;
	std::vector<Przesylka> s_paczki;
	char s_znak_charakterystyczny;
	//MAX_PACZEK - oznacza ile maksymalnie paczek moze pomiescic samochod
	unsigned s_MAX_PACZEK;
	//WSP_PREDK - oznacza on ile razy podany samochod musi wykonac "ruch" aby osiagnac swoj cel
	//czym wiekszy WSP_PREDK tym wiecej czasu potrzeba aby samochod wykonal widoczny postep w jezdzie
	unsigned s_WSP_PREDK;
	//zmienna postep przechowuje informacje o aktualnym postepie samochodu
	//gdy postep = WSP_PREDK to samochod wykonuje widoczny postep, czyli przeprowadza okreslone dzialanie
	int s_postep;
	std::string s_docelowe_miejsce;
public:
	Samochod(void);
	Samochod(char znak_charakterystyczny, unsigned MAX_PACZEK, unsigned WSP_PREDK);
	Przesylka wypakuj_przesylke(void);
	//wirtualny destruktor
	virtual ~Samochod(void);
	bool dodaj_towar(Przesylka paczka);
	int wydaj_paczki(Klient &odbiorca);
	void pokaz_zawartosc_samochodu(void);
	bool zwieksz_postep(void);
	//wirtualna metoda, w klasach pochodnych istnieje metoda o identycznej nazwie
	virtual std::string wyswietl_informacje(void);
	char zwroc_znak_charakt(void) {return s_znak_charakterystyczny;};
	bool sprawdz_czy_pusty(void) {return s_paczki.empty();};
	void zmien_docelowe_miejsce(std::string docelowe_miejsce);
	std::string zwroc_docelowe_miejsce(void) {return s_docelowe_miejsce;};
	Klient zwroc_adresata_losowej_przesylki(void);
	int zwroc_ilosc_przesylek(void) {return s_paczki.size();};
};

//klasa samochodow Ford Transist
class Ford_Transist: public Samochod
{
public:
	Ford_Transist(void);
	~Ford_Transist(void);
	static void Ford_Transist_informacje(void);
	std::string wyswietl_informacje(void);
}; 

//klasa samochodow Renault Master
class Renault_Master: public Samochod
{
public:
	Renault_Master(void);
	~Renault_Master(void);
	static void Renault_Master_informacje(void);
	std::string wyswietl_informacje(void);
};

//klasa samochodow Volkswagen Caddy
class Volkswagen_Caddy: public Samochod
{
public:
	Volkswagen_Caddy(void);
	~Volkswagen_Caddy(void);
	static void Volkswagen_Caddy_informacje(void);
	std::string wyswietl_informacje(void);
};

#endif
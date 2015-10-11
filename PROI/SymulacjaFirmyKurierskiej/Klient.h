//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#ifndef KLIENT_H
#define KLIENT_H
#include <iostream>	
#include <string>
#include <stdlib.h>	//funkcja rand()
#include <vector>
#include <queue>
#include <fstream> //dolaczone w celu zapisywania wynikow symulacji do pliku
#include <sstream> //aby moc korzystac z stringstream
#include <Windows.h>

class Klient
{
private:
	std::string k_nazwisko;
	std::string k_imie;
	std::string k_lokalizacja;
	std::string k_adres_zamieszkania;
public:
	Klient(void);
	Klient(std::string tablica_danych[4]);
	~Klient(void);
	void wyswietl_informacje(void);
	static bool poprawna_lokalizacja(std::string lokalizacja);
	bool operator==(const Klient &klient);
	std::string zwroc_lokalizacje(void) {return k_lokalizacja;};
	std::string wyswietl_nazwisko_imie(void);
};

#endif

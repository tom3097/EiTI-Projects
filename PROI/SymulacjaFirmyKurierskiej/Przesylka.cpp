//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#include "Przesylka.h"

//konstruktor domyslny
Przesylka::Przesylka(void)
{
	p_odbiorca_przesylki = Klient();
	numer_ID_przesylki = 0;
}

//konstruktor z parametrem, uzupelnia odbiorce przesylki oraz numer ID przesylki
Przesylka::Przesylka(const Klient &odbiorca)
{
	p_odbiorca_przesylki = odbiorca;
	numer_ID_przesylki = rand()%1000 + 1;
}

//destruktor
Przesylka::~Przesylka(void)
{
}

//metoda wyswietlajaca szczegolowe informacje na temat przesylki
void Przesylka::wyswietl_dane(void)
{
	std::cout<<"\t***NUMER ID PRZESYLKI*** "<<std::endl;
	std::cout<<"\t\t"<<numer_ID_przesylki<<std::endl;
	std::cout<<"\t***ODBIORCA PRZESYLKI*** "<<std::endl;
	p_odbiorca_przesylki.wyswietl_informacje();
}
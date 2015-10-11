//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#include "Klient.h"

//globalnie zadeklarowany wektor przechowujacy wszystkie dostepne lokalizacje obslugiwane przez firme
//gdy podana przez uzytkownika lokalizacja klienta jest inna niz dostepne lokalizacje obslugiwane przez firme
//klient nie zostanie dodany
std::vector<std::string> dozwolone_lokalizacje;

//konstruktor domyslny, wszystkim zmiennym przypisuje "brak danych"
Klient::Klient(void)
{
	k_nazwisko = "brak danych";
	k_imie = "brak danych";
	k_lokalizacja = "brak danych";
	k_adres_zamieszkania = "brak danych";
}

//konstruktor z parametrem, uzupelnia wszystkie dane klienta
Klient::Klient(std::string tablica_danych[4])
{
	k_nazwisko = tablica_danych[0];
	k_imie = tablica_danych[1];
	k_lokalizacja = tablica_danych[2];
	k_adres_zamieszkania = tablica_danych[3];
}

//metoda wyswietlajaca nazwisko i imie klienta
std::string Klient::wyswietl_nazwisko_imie(void)
{
	std::stringstream dane;
	dane<<k_nazwisko<<" "<<k_imie<<"\n";
	return dane.str();
}

//destruktor
Klient::~Klient(void)
{
}

//metoda statyczna, sprawdza czy podana lokalizacje znajduje sie w wektorze dostepnych lokalizacji,
//inaczej mowiac, sprawdza czy kandydat na klienta o podanej lokalizacji moze zostac klientem firmy
//jesli wynik sprawdzania jest pozytywny to zwraca true, jesli negatywny to false
bool Klient::poprawna_lokalizacja(std::string lokalizacja)
{
	for(unsigned i=0; i<dozwolone_lokalizacje.size(); i++)
	{
		if(lokalizacja == dozwolone_lokalizacje[i])
			return true;
	}
	return false;
}

//metoda wyswietlajaca szczegolowe informacje o kliencie
void Klient::wyswietl_informacje(void)
{
	std::cout<<"Nazwisko: "<<k_nazwisko<<std::endl;
	std::cout<<"Imie: "<<k_imie<<std::endl;
	std::cout<<"Lokalizacja: "<<k_lokalizacja<<std::endl;
	std::cout<<"Adres zamieszkania: "<<k_adres_zamieszkania<<std::endl;
}

//przeciazenie operatora ==, wykorzystywany do porownywania klientow
bool Klient::operator==(const Klient &klient)
{
	if(k_nazwisko != klient.k_nazwisko)
		return false;
	if(k_imie != klient.k_imie)
		return false;
	if(k_lokalizacja != klient.k_lokalizacja)
		return false;
	if(k_adres_zamieszkania != klient.k_adres_zamieszkania)
		return false;

	return true;
}

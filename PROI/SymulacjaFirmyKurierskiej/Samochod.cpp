//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#include "Samochod.h"

//konstruktor domyslny
Samochod::Samochod(void)
{
	s_numer_ID_pojazdu = 0;
	s_znak_charakterystyczny = 'B';
	s_MAX_PACZEK = 0;
	s_WSP_PREDK = 0;
	s_postep = 0;
	s_docelowe_miejsce = "brak danych";
}

//konstruktor z parametrem, pobiera znak charakterystyczny samochodu oraz dwie informacje: max_paczek, wsp_predk
Samochod::Samochod(char znak_charakterystyczny, unsigned max_paczek, unsigned wsp_predk)
{
	s_numer_ID_pojazdu = rand()%1000 +1;
	s_znak_charakterystyczny = znak_charakterystyczny;
	s_MAX_PACZEK = max_paczek;
	s_WSP_PREDK = wsp_predk;
	s_postep = 0;
	s_docelowe_miejsce = "brak danych";
}

//metoda do wypakowania przesylki z samochodu
//metoda zwraca przesylke ktora usunela z samochodu
Przesylka Samochod::wypakuj_przesylke(void)
{
	if(!s_paczki.empty())
	{
		Przesylka tmp = s_paczki.front();
		s_paczki.erase(s_paczki.begin());
		return tmp;
	}
	else return Przesylka();
}

//metoda zmieniajaca docelowe miejsce samochodu
void Samochod::zmien_docelowe_miejsce(std::string docelowe_miejsce)
{
	s_docelowe_miejsce = docelowe_miejsce;
}

//metoda dodajaca paczke do samochodu
//w wyniku niepowodzenia dodawania z powodu braku miejsca w samochodzie metoda zwraca false
bool Samochod::dodaj_towar(Przesylka paczka)
{
	if(s_paczki.size() < s_MAX_PACZEK)
	{
		s_paczki.push_back(paczka);
		return true;
	}
	return false;
}

//metoda pobiera klienta i przeszukuje zawartosc samochodow
//gdy znajdzie paczke przeznaczona dla podanego klienta usuwa ja z samochodu (oddaje odbiorcy)
//metoda zwraca liczbe przesylek oddanych klientowi
int Samochod::wydaj_paczki(Klient &odbiorca)
{
	int wykonaj = s_paczki.size();
	int liczba_wykonan = 0;
	int indeks_do_sprawdzenia = 0;
	int liczba_wydanych_paczek = 0;

	while(liczba_wykonan != wykonaj)
	{

		if(s_paczki[indeks_do_sprawdzenia].zwroc_odbiorce() == odbiorca)
		{
			++liczba_wydanych_paczek;
			s_paczki.erase(s_paczki.begin()+indeks_do_sprawdzenia);
			--indeks_do_sprawdzenia;
		}
	++liczba_wykonan;
	++indeks_do_sprawdzenia;
	}
	return liczba_wydanych_paczek;
}

//metoda zwracajaca adres losowego klienta
Klient Samochod::zwroc_adresata_losowej_przesylki(void)
{
	int los_index = rand()%s_paczki.size();
	Klient losowo_wybrany = s_paczki[los_index].zwroc_odbiorce();
	return losowo_wybrany;
}

//destruktor
Samochod::~Samochod(void)
{
}

//wyswietla zawartosc samochodu, czyli paczki ktore aktualnie przetrzymuje
void Samochod::pokaz_zawartosc_samochodu(void)
{
	if(s_paczki.empty())
		std::cout<<"Samochod jest pusty.\n";
	else
	{
		std::cout<<"\t***ZAWARTOSC SAMOCHODU*** "<<std::endl;
		for(unsigned i=0; i<s_paczki.size(); i++)
			s_paczki[i].wyswietl_dane();
	}
}

//zwieksza postep ruchu samochodow
//gdy postep = WSP_PREDK, zmienna postep jest zerowana, a metoda zwraca true
//metoda zwraca true gdy wykonano widoczny postep, false gdy postep wykonany przez samochod nie jest jeszcze widoczny
bool Samochod::zwieksz_postep(void)
{
	++s_postep;
	if(s_postep == s_WSP_PREDK)
	{
		s_postep = 0;
		return true;
	}
	return false;
}

//wyswietla informacje o samochodzie
std::string Samochod::wyswietl_informacje(void)
{
	std::stringstream informacje;
	informacje<<s_numer_ID_pojazdu;
	return informacje.str();
}

//konstruktor klasy pochodnej
Ford_Transist::Ford_Transist(void): Samochod('F',30,2)
{
}

//destruktor klasy pochodnej
Ford_Transist::~Ford_Transist(void)
{
}

//metoda statyczna, wyswietla szczegolowe informacje podanym typie samochodu
void Ford_Transist::Ford_Transist_informacje(void)
{
	std::cout<<"Nazwa samochodu: Ford Transist\n";
	std::cout<<"Typ: samochod dostawczy\n";
	std::cout<<"Maksymalny ladunek: 30\n";
	std::cout<<"Wspolczynnik szybkosci: 2\n";
}

//metoda, wyswietla informacje o konkretnym samochodzie
std::string Ford_Transist::wyswietl_informacje(void)
{
	std::stringstream info;
	info<<"Ford Transist, ID "<<Samochod::wyswietl_informacje();
	return info.str();
}

//konstruktor klasy pochodnej
Renault_Master::Renault_Master(void): Samochod('R',50,3)
{
}

//destruktor klasy pochodnej
Renault_Master::~Renault_Master(void)
{
}

//metoda statyczna, wyswietla szczegolowe informacje podanym typie samochodu
void Renault_Master::Renault_Master_informacje(void)
{
	std::cout<<"Nazwa samochodu: Renault Master\n";
	std::cout<<"Typ: lekki samochod ciezarowy\n";
	std::cout<<"Maksymalny ladunek: 50\n";
	std::cout<<"Wspolczynnik szybkosci: 3\n";
}

//metoda, wyswietla informacje o konkretnym samochodzie
std::string Renault_Master::wyswietl_informacje(void)
{
	std::stringstream info;
	info<<"Renault Master, ID "<<Samochod::wyswietl_informacje();
	return info.str();
}

//konstruktor klasy pochodnej
Volkswagen_Caddy::Volkswagen_Caddy(void): Samochod('V',15,1)
{
}

//destruktor klasy pochodnej
Volkswagen_Caddy::~Volkswagen_Caddy(void)
{
}

//metoda statyczna, wyswietla szczegolowe informacje podanym typie samochodu
void Volkswagen_Caddy::Volkswagen_Caddy_informacje(void)
{
	std::cout<<"Nazwa samochodu: Renault Master\n";
	std::cout<<"Typ: lekki samochod ciezarowy\n";
	std::cout<<"Maksymalny ladunek: 15\n";
	std::cout<<"Wspolczynnik szybkosci: 1\n";
}

//metoda, wyswietla informacje o konkretnym samochodzie
std::string Volkswagen_Caddy::wyswietl_informacje(void)
{
	std::stringstream info;
	info<<"Volkswagen Caddy, ID "<<Samochod::wyswietl_informacje();
	return info.str();
}
//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#include "Placowka.h"

//globalny wektor, sluzy do przekazywania przesylek miedzy baza a oddzialami
//przesylki nie sa tworzone od nowa na potrzeby przekazania ich do oddzialu.
//poniewaz kazda przeslka posiada numer ID,
//ponadto taka forma przekazywania przesylek miedzy obiektem baza a obiektami oddzial 
//bardziej odzwierciedla dzialanie firmy kurierskiej
std::vector<tymczasowa_przestrzen> vector_przestrzeni;

//konstruktor domyslny
Placowka::Placowka(void)
{
	p_typ_placowki = "brak danych";
	p_lokalizacja = "brak danych";
	ilosc_Ford_Transist_oczekujacych = 0;
	ilosc_Renault_Master_oczekujacych = 0;
	ilosc_Volkswagen_Caddy_oczekujacych = 0;
}

//konstruktor z parametrem
Placowka::Placowka(std::string typ_placowki, std::string lokalizacja)
{
	p_typ_placowki = typ_placowki;
	p_lokalizacja = lokalizacja;
	ilosc_Ford_Transist_oczekujacych = 0;
	ilosc_Renault_Master_oczekujacych = 0;
	ilosc_Volkswagen_Caddy_oczekujacych = 0;
}

//metoda znajdujaca odpowiednia przestrzen, z ktorej ladowane sa przesylki do oddzialu
//wczesniej przesylki zostaly dostarczone do tej przestrzeni za pomoca samochodow z bazy
int Placowka::znajdz_przestrzen(std::string lokalizacja)
{
	int index;
	for(unsigned i=0; i< vector_przestrzeni.size(); i++)
	{
		if(lokalizacja == vector_przestrzeni[i].lokalizacja)
		{
			index = i;
			break;
		}
	}
	return index;
}

//destruktor
Placowka::~Placowka(void)
{
	Samochod *to_kill;
	while(!p_kolejka_samochodow_oczekujacych.empty())
	{
		to_kill = p_kolejka_samochodow_oczekujacych.front();
		p_kolejka_samochodow_oczekujacych.pop();
		delete to_kill;
	}
}

//wyswietla informacje o placowce
void Placowka::informacje_o_placowce(void)
{
	std::cout<<"Typ placowki: "<<p_typ_placowki<<", Lokalizacja: "<<p_lokalizacja<<std::endl;
}

//metoda dodajaca samochod do placowki
//typy samochodow dodawane sa losowo, urzytkownik decyduje tylko o ilosci samochodow
void Placowka::dodaj_samochod(void)
{
	Samochod *nowy;
	int wybor = rand()%3;
	
	std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	informacje_o_placowce();
	std::cout<<"Samochod zostal dodany.\n";
	std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";

	if(wybor == 0)
	{
		nowy = new Ford_Transist;
		p_kolejka_samochodow_oczekujacych.push(nowy);
		++ilosc_Ford_Transist_oczekujacych;
		return;
	}
	if(wybor == 1)
	{
		nowy = new Renault_Master;
		p_kolejka_samochodow_oczekujacych.push(nowy);
		++ilosc_Renault_Master_oczekujacych;
		return;
	}
	if(wybor == 2)
	{
		nowy = new Volkswagen_Caddy;
		p_kolejka_samochodow_oczekujacych.push(nowy);
		++ilosc_Volkswagen_Caddy_oczekujacych;
		return;
	}
}

//metoda usuwajaca samochod z oddzialu, o ile w tym oddziale znajduja sie samochody
//metoda usuwa pierwszy samochod z kolejki samochodow oczekujacych
void Placowka::usun_samochod(void)
{
	if(p_kolejka_samochodow_oczekujacych.empty() == false)
	{
		Samochod *to_kill = p_kolejka_samochodow_oczekujacych.front();
		switch(p_kolejka_samochodow_oczekujacych.front()->zwroc_znak_charakt())
		{
		case 'F': --ilosc_Ford_Transist_oczekujacych; break;
		case 'R': --ilosc_Renault_Master_oczekujacych; break;
		case 'V': --ilosc_Volkswagen_Caddy_oczekujacych; break;
		}
		p_kolejka_samochodow_oczekujacych.pop();
		delete to_kill;
		std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
		informacje_o_placowce();
		std::cout<<"Samochod zostal usuniety.\n";
		std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	}
	else
	{
		std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
		informacje_o_placowce();
		std::cout<<"W placowce nie ma juz samochodow.\n";
		std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	}
}

//metoda wyswietlajaca stan samochodow w placowce
void Placowka::wyswietl_stan_samochodow(void)
{
	std::cout<<"Liczba samochodow: "<<p_kolejka_samochodow_oczekujacych.size()<<",";
	std::cout<<"Ford Transist x "<<ilosc_Ford_Transist_oczekujacych<<",";
	std::cout<<"Renault Master x "<<ilosc_Renault_Master_oczekujacych<<",";
	std::cout<<"Volkswagen Caddy x "<<ilosc_Volkswagen_Caddy_oczekujacych<<".\n";
}

//metoda usuwajaca samochod z wektora samochodow podrozujacych
//i dodajaca go do kolejki samochodow oczekujacych na wyjazd z placowki
void Placowka::wroc_do_placowki(int numer)
{
	Samochod *tmp = p_vektor_samochodow_podrozujacych[numer];

	if(numer == p_vektor_samochodow_podrozujacych.size()-1)
		p_vektor_samochodow_podrozujacych.pop_back();
	else
		p_vektor_samochodow_podrozujacych.erase(p_vektor_samochodow_podrozujacych.begin()+numer);
	p_kolejka_samochodow_oczekujacych.push(tmp);
}
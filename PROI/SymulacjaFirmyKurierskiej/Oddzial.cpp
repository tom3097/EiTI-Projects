//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#include "Oddzial.h"

extern std::vector<std::string> dozwolone_lokalizacje;
extern std::vector<tymczasowa_przestrzen> vector_przestrzeni;

extern std::ofstream plik_wynikowy;

//konstruktor domyslny
Oddzial::Oddzial(void)
{
}

//konstruktor z parametrem
Oddzial::Oddzial(std::string lokalizacja_oddz): Placowka("ODDZIAL",lokalizacja_oddz)
{
	//tworzony zostaje nowy oddzial
	//lokalizacja oddzialu zostaje dodana do dostepnych lokalizacji
	//zostaje stworzona tymczasowa przestrzen dla przesylek przesylanych z bazy wlasnie do tego oddzialu
	dozwolone_lokalizacje.push_back(lokalizacja_oddz);
	tymczasowa_przestrzen nowa_przestrzen;
	nowa_przestrzen.lokalizacja = lokalizacja_oddz;
	vector_przestrzeni.push_back(nowa_przestrzen);
}

//destruktor
Oddzial::~Oddzial(void)
{
	//usuwana zostaje tymczasowa przestrzen oddzialu
	for(unsigned i=0; i< vector_przestrzeni.size(); i++)
	{
		if(p_lokalizacja == vector_przestrzeni[i].lokalizacja)
		{
			if(i == vector_przestrzeni.size() -1)
				vector_przestrzeni.pop_back();
			else
				vector_przestrzeni.erase(vector_przestrzeni.begin()+i);
			break;
		}
	}

	//lokalizacja oddzialu zostaje usunieta z dozwolonych lokalizacji
	for(unsigned i=0; i< dozwolone_lokalizacje.size(); i++)
	{
		if(p_lokalizacja == dozwolone_lokalizacje[i])
		{
			if(i == dozwolone_lokalizacje.size()-1)
				dozwolone_lokalizacje.pop_back();
			else
				dozwolone_lokalizacje.erase(dozwolone_lokalizacje.begin()+i);
			break;
		}
	}
}

//metoda, przesylki z tymczasowej przestrzeni przekazywane sa do kolejki przesylek w oddziale
//po przekazaniu tymczasowa przestrzen oddzialu jest pusta
void Oddzial::przyjmij_przesylki(void)
{
	std::string lokalizacja = zwroc_lokalizacje();
	int index = znajdz_przestrzen(lokalizacja);
	Przesylka tmp_przesylka;

	while(!vector_przestrzeni[index].tmp_przestrzen.empty())
	{
		tmp_przesylka = vector_przestrzeni[index].tmp_przestrzen.front();
		vector_przestrzeni[index].tmp_przestrzen.erase(vector_przestrzeni[index].tmp_przestrzen.begin());
		kolejka_przesylek.push(tmp_przesylka);
	}
}

//metoda ladujaca samochod w oddziale
void Oddzial::zaladuj_samochod(void)
{
	//sprawdzanie czy w oddziale obecne sa samochody
	if(!p_kolejka_samochodow_oczekujacych.empty())
	{
		//jesli pierwszy samochod w kolejce jest juz zaladowany (czyli ma co najmniej 1 paczke)
		//przenoszony jest z kolejki samochodow oczekujacych do wektora samochodow podrozujacych
		if(!p_kolejka_samochodow_oczekujacych.front()->sprawdz_czy_pusty())
		{
			Samochod * tmp_samochod = p_kolejka_samochodow_oczekujacych.front();
			p_vektor_samochodow_podrozujacych.push_back(tmp_samochod);
			p_kolejka_samochodow_oczekujacych.pop();
		}

		//jesli kolejka samochodow nie jest pusta i w oddziale sa przesylki nastepuje ladowanie ich do samochodu
		if( !p_kolejka_samochodow_oczekujacych.empty() && !kolejka_przesylek.empty())
		{
			unsigned ilosc_paczek_w_kolejce = kolejka_przesylek.size();
			unsigned zapakowane_do_samochodu = 0;
			Przesylka tmp_paczka;

			for(unsigned i=0; i<ilosc_paczek_w_kolejce; i++)
			{
				tmp_paczka = kolejka_przesylek.front();
				if(p_kolejka_samochodow_oczekujacych.front()->dodaj_towar(tmp_paczka))
				{
					kolejka_przesylek.pop();
					++zapakowane_do_samochodu;
				}
				else
					break;
			}
			std::cout<<"*----------------------------------------------------------------------------*\n";
			std::cout<<p_kolejka_samochodow_oczekujacych.front()->wyswietl_informacje();
			std::cout<<", zapakowano przesylki: "<<zapakowane_do_samochodu;
			std::cout<<", z oddzialu: "<<zwroc_lokalizacje()<<std::endl;
			std::cout<<"*----------------------------------------------------------------------------*\n";
			if(plik_wynikowy.is_open())
			{
				plik_wynikowy<<"*----------------------------------------------------------------------------*\n";
				plik_wynikowy<<p_kolejka_samochodow_oczekujacych.front()->wyswietl_informacje();
				plik_wynikowy<<", zapakowano przesylki: "<<zapakowane_do_samochodu;
				plik_wynikowy<<", z oddzialu: "<<zwroc_lokalizacje()<<"\n";
				plik_wynikowy<<"*----------------------------------------------------------------------------*\n";
			}
		}
	}
}

//metoda sluzaca do rozwozenia przesylek
void Oddzial::rozwoz_przesylki_z_oddzialu(void)
{
	//najpirw nastepuje przyjecie przesylek z tymczasowej przestrzeni
	przyjmij_przesylki();

	unsigned ilosc_w_drodze = p_vektor_samochodow_podrozujacych.size();
	unsigned wykonano = 0;
	unsigned index = 0;

	int czas = rand()%1000 + 2000;
		Sleep(czas);

	//nastepuje ladowanie samochodu
	zaladuj_samochod();

	//dla kazdego samochodu ktory znajduje sie w drodze zwiekszany jest postep
	while(wykonano != ilosc_w_drodze)
	{
		int czas = rand()%1000 + 2000;
		Sleep(czas);

		bool postep = p_vektor_samochodow_podrozujacych[index]->zwieksz_postep();
		//jesli wykonano widoczny postep i samochod nie jest pusty wybierany jest losowy klient
		//ktory zostaje obsluzony (dostarczone sa do niego przesylki)
		if(postep && !p_vektor_samochodow_podrozujacych[index]->sprawdz_czy_pusty())
		{
			Klient wybrany = p_vektor_samochodow_podrozujacych[index]->zwroc_adresata_losowej_przesylki();
			int ilosc = p_vektor_samochodow_podrozujacych[index]->wydaj_paczki(wybrany);

			std::cout<<"*----------------------------------------------------------------------------*\n";
			std::cout<<p_vektor_samochodow_podrozujacych[index]->wyswietl_informacje();
			std::cout<<", wydano paczki: "<<ilosc;
			std::cout<<", klientowi: ";
			std::cout<<wybrany.wyswietl_nazwisko_imie();
			std::cout<<"*----------------------------------------------------------------------------*\n";

			if(plik_wynikowy.is_open())
			{
				plik_wynikowy<<"*----------------------------------------------------------------------------*\n";
				plik_wynikowy<<p_vektor_samochodow_podrozujacych[index]->wyswietl_informacje();
				plik_wynikowy<<", wydano paczki: "<<ilosc;
				plik_wynikowy<<", klientowi: ";
				plik_wynikowy<<wybrany.wyswietl_nazwisko_imie();
				plik_wynikowy<<"*----------------------------------------------------------------------------*\n";
			}
		}

		//jesli wykonano widoczny postep i samochod jest pusty to zostaje on przyjety do oddzialu, placowki
		else if(postep && p_vektor_samochodow_podrozujacych[index]->sprawdz_czy_pusty())
		{
			std::cout<<"*----------------------------------------------------------------------------*\n";
			std::cout<<p_vektor_samochodow_podrozujacych[index]->wyswietl_informacje();
			std::cout<<", wrocil do oddzialu: "<<zwroc_lokalizacje()<<std::endl;
			std::cout<<"*----------------------------------------------------------------------------*\n";

			if(plik_wynikowy.is_open())
			{
				plik_wynikowy<<"*----------------------------------------------------------------------------*\n";
				plik_wynikowy<<p_vektor_samochodow_podrozujacych[index]->wyswietl_informacje();
				plik_wynikowy<<", wrocil do oddzialu: "<<zwroc_lokalizacje()<<"\n";
				plik_wynikowy<<"*----------------------------------------------------------------------------*\n";
			}

			wroc_do_placowki(index);
			--index;
		}
		++wykonano;
		++index;
	}
}
			
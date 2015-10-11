//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#include "Baza.h"

extern std::vector<tymczasowa_przestrzen> vector_przestrzeni;
extern std::vector<std::string> dozwolone_lokalizacje;

extern std::ofstream plik_wynikowy;

//konstruktor domyslny
Baza::Baza(void)
{
}

//konstruktor z parametrem
Baza::Baza(std::string lokalizacja): Placowka("BAZA",lokalizacja)
{
}

//destruktor
Baza::~Baza(void)
{
	b_baza_klientow.clear();
}

//metoda sluzaca do dodawania klienta przez urzytkownika
void Baza::dodaj_klienta(std::string tab_klient[4])
{
	Klient klient_do_dodania(tab_klient);

	if(Klient::poprawna_lokalizacja(tab_klient[2]))
	{
		unsigned rozmiar = b_baza_klientow.size();
		for(unsigned i=0; i<rozmiar; i++)
		{
			if(b_baza_klientow[i] == klient_do_dodania)
			{
				std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
				std::cout<<"Podana osoba jest juz zarejestrowana jako klient.\n";
				std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
				return;
			}
		}
		b_baza_klientow.push_back(klient_do_dodania);
		std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
		std::cout<<"Klient zostal dodany: \n";
		klient_do_dodania.wyswietl_informacje();
		std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	}
}

//metoda sluzaca do usuwanie klienta przez urzytkownika
void Baza::usun_klienta(std::string tab_klient[4])
{
	Klient klient_do_usuniecia (tab_klient);

	if(Klient::poprawna_lokalizacja(tab_klient[2]))
	{
		unsigned rozmiar = b_baza_klientow.size();
		for(unsigned i=0; i<rozmiar; i++)
		{
			if(b_baza_klientow[i] == klient_do_usuniecia)
			{
				if(i == b_baza_klientow.size() - 1)
					b_baza_klientow.pop_back();
				else
					b_baza_klientow.erase(b_baza_klientow.begin()+i);
				std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
				std::cout<<"Klient zostal usuniety.\n";
				std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
				return;
			}
		}
		std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
		std::cout<<"Podany klient nie istnieje.\n";
		std::cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	}
}

//wyswietlanie listy klientow zarejestrowanych w bazie
void Baza::wyswietl_klientow(void)
{
	for(unsigned i=0; i<b_baza_klientow.size(); i++)
	{
		b_baza_klientow[i].wyswietl_informacje();
		std::cout<<std::endl;
	}
}

//metoda generujaca przesylki
//ilosc przesylke zalezy od liczby klientow
void Baza::generuj_przesylki(void)
{
	unsigned ilosc_klientow = b_baza_klientow.size();
	
	for(unsigned i=0; i<ilosc_klientow; i++)
	{
		unsigned ilosc_pacz = 3+ rand()%4;
		for(unsigned j=0; j<ilosc_pacz; j++)
		{
			Przesylka nowa_przesylka(b_baza_klientow[i]);
			b_przesylki_w_bazie.push_back(nowa_przesylka);
		}
	}
}

//metoda sluzaca do ladowania samochodu
void Baza::zaladuj_samochod(void)
{
	//sprawdzanie czy w bazie znajduja sie samochody
	if(!p_kolejka_samochodow_oczekujacych.empty())
	{
		//jesli pierwszy samochod w kolejce nie jest pusty usuwany jest on z kolejki
		//i przekazywany do wektora samochodow znajdujacych sie w drodze
		if(!p_kolejka_samochodow_oczekujacych.front()->sprawdz_czy_pusty())
		{
			Samochod * tmp_samochod = p_kolejka_samochodow_oczekujacych.front();
			p_vektor_samochodow_podrozujacych.push_back(tmp_samochod);
			p_kolejka_samochodow_oczekujacych.pop();
		}

		//jesli w bazie sa samochody i przesylki samochod zostanie zaladowany przesylkami
		if(!p_kolejka_samochodow_oczekujacych.empty() && !b_przesylki_w_bazie.empty())
		{
			std::string wybrana_lokalizacja = b_przesylki_w_bazie.front().zwroc_odbiorce().zwroc_lokalizacje();
			unsigned wykonaj = b_przesylki_w_bazie.size();
			p_kolejka_samochodow_oczekujacych.front()->zmien_docelowe_miejsce(wybrana_lokalizacja);
			unsigned liczba_wykonan =0;
			int index = 0;
			int liczba_przesylek = 0;

			while(liczba_wykonan != wykonaj)
			{
				if(wybrana_lokalizacja == b_przesylki_w_bazie[index].zwroc_odbiorce().zwroc_lokalizacje())
				{
					Przesylka tmp = b_przesylki_w_bazie[index];
		
					if(p_kolejka_samochodow_oczekujacych.front()->dodaj_towar(tmp))
					{
						++liczba_przesylek;
						if(index == wykonaj-1)
						{
							b_przesylki_w_bazie.pop_back();
						}
						else
						{
							b_przesylki_w_bazie.erase(b_przesylki_w_bazie.begin()+index);
						}
						--index;
					}
					else
						break;
				}
				++liczba_wykonan;
				++index;
			}
			std::cout<<"***------------------------------------------------------------------------***\n";
			std::cout<<p_kolejka_samochodow_oczekujacych.front()->wyswietl_informacje();
			std::cout<<", zaladowano przesylki: "<<liczba_przesylek;
			std::cout<<", dla oddzialu: "<<p_kolejka_samochodow_oczekujacych.front()->zwroc_docelowe_miejsce()<<std::endl;
			std::cout<<"***------------------------------------------------------------------------***\n";

			if(plik_wynikowy.is_open())
			{
				plik_wynikowy<<"***------------------------------------------------------------------------***\n";
				plik_wynikowy<<p_kolejka_samochodow_oczekujacych.front()->wyswietl_informacje();
				plik_wynikowy<<", zaladowano przesylki: "<<liczba_przesylek;
				plik_wynikowy<<", dla oddzialu: "<<p_kolejka_samochodow_oczekujacych.front()->zwroc_docelowe_miejsce()<<"\n";
				plik_wynikowy<<"***------------------------------------------------------------------------***\n";
			}
		}
	}
}

//metoda sluzaca do usuwania samochodu z wektora samochodow w dordze
//i dodawaniu do kolejki w bazie
void Baza::wroc_do_bazy(int numer)
{
	p_vektor_samochodow_podrozujacych[numer]->zmien_docelowe_miejsce("brak danych");
	Placowka::wroc_do_placowki(numer);
}

//metoda do wyladowania samochodu
//znajdowana jest odpowiednia przestrzen do ktorej przekazywane sa przesylki
//potem z tej przestrzeni przesylki trafiaja do odpowiedniego oddzialu
void Baza::wyladuj_samochod(int numer)
{
	Przesylka tmp;
	std::string cel_podrozy = p_vektor_samochodow_podrozujacych[numer]->zwroc_docelowe_miejsce();

	int index = znajdz_przestrzen(cel_podrozy);

	while(!p_vektor_samochodow_podrozujacych[numer]->sprawdz_czy_pusty())
	{
		tmp = p_vektor_samochodow_podrozujacych[numer]->wypakuj_przesylke();
		vector_przestrzeni[index].tmp_przestrzen.push_back(tmp);
	}
}

//metoda rozwozaca przesylki
void Baza::rozwoz_przesylki_z_bazy(void)
{
	unsigned ilosc = p_vektor_samochodow_podrozujacych.size();
	unsigned wykonano= 0;
	int index =0;

	int czas = rand()%1000 + 2000;
		Sleep(czas);

	zaladuj_samochod();
	while(wykonano != ilosc)
	{
		int czas = rand()%1000 + 2000;
		Sleep(czas);

		bool postep = p_vektor_samochodow_podrozujacych[index]->zwieksz_postep();
		//jesli samochod wykonal widoczny postep i nie jest pusty to przewozone przez niego
		//przesylki wyladowywane sa do odpowiedniej przestrzeni tymczasowej
		if(postep && !p_vektor_samochodow_podrozujacych[index]->sprawdz_czy_pusty())
		{
			std::cout<<"***------------------------------------------------------------------------***\n";
			std::cout<<p_vektor_samochodow_podrozujacych[index]->wyswietl_informacje();
			std::cout<<", wyladowano przesylki: "<<p_vektor_samochodow_podrozujacych[index]->zwroc_ilosc_przesylek();
			std::cout<<", w oddziale: "<<p_vektor_samochodow_podrozujacych[index]->zwroc_docelowe_miejsce()<<std::endl;
			std::cout<<"***------------------------------------------------------------------------***\n";

			if(plik_wynikowy.is_open())
			{
				plik_wynikowy<<"***------------------------------------------------------------------------***\n";
				plik_wynikowy<<p_vektor_samochodow_podrozujacych[index]->wyswietl_informacje();
				plik_wynikowy<<", wyladowano przesylki: "<<p_vektor_samochodow_podrozujacych[index]->zwroc_ilosc_przesylek();
				plik_wynikowy<<", w oddziale: "<<p_vektor_samochodow_podrozujacych[index]->zwroc_docelowe_miejsce()<<"\n";
				plik_wynikowy<<"***------------------------------------------------------------------------***\n";
			}

			wyladuj_samochod(index);
		}
		//jesli samochod wykonal widoczny postep i jest pusty to wraca do bazy
		else if(postep && p_vektor_samochodow_podrozujacych[index]->sprawdz_czy_pusty())
		{
			std::cout<<"***------------------------------------------------------------------------***\n";
			std::cout<<p_vektor_samochodow_podrozujacych[index]->wyswietl_informacje();
			std::cout<<", wrocil do Bazy"<<std::endl;
			std::cout<<"***------------------------------------------------------------------------***\n";

			if(plik_wynikowy.is_open())
			{
				plik_wynikowy<<"***------------------------------------------------------------------------***\n";
				plik_wynikowy<<p_vektor_samochodow_podrozujacych[index]->wyswietl_informacje();
				plik_wynikowy<<", wrocil do Bazy"<<"\n";
				plik_wynikowy<<"***------------------------------------------------------------------------***\n";
			}

			wroc_do_bazy(index);
			--index;
		};

		++index;
		++wykonano;
	}
}

//metoda usuwajaca niekatualnych klientow
//jesli oddzial zostal zlikwidowany metoda usuwa kientow ktorych obslugiwal oddzial
void Baza::usun_nieaktualnych_klientow(void)
{
	bool usuwac;
	int ilosc_wykonan = b_baza_klientow.size();
	int wykonano = 0;
	int index = 0;

	while(wykonano != ilosc_wykonan)
	{
		usuwac = true;
		for(unsigned j=0; j<dozwolone_lokalizacje.size(); j++)
		{
			if(b_baza_klientow[index].zwroc_lokalizacje() == dozwolone_lokalizacje[j])
			{
				usuwac = false;
				break;
			}
		}

		if(usuwac == true)
		{
			if(index == b_baza_klientow.size()-1)
				b_baza_klientow.pop_back();
			else
				b_baza_klientow.erase(b_baza_klientow.begin()+index);
			--index;
		}
		++wykonano;
		++index;
	}
}

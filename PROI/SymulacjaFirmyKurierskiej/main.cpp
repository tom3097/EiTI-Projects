//Projekt 3: Symulacja Firmy Kurierskiej
//Przygotowal: Tomasz Bochenski
//Prowadzacy: Piotr Witoñski

#include <iostream>
#include "Baza.h"
#include "Oddzial.h"

using namespace std;

Baza baza_firmy("Warszawa");
vector<Oddzial*> wektor_oddzialow;

ofstream plik_wynikowy;

void instrukcja_1(void);
void instrukcja_2(void);
void podstawowe_informacje_o_firmie(void);
void informacje_o_stanie_klientow(void);
void informacje_o_samochodach_firmy(void);
void informacje_o_samochodach_bazy(void);
void informacje_o_samochodach_oddzialu(string lokalizacja);
void usun_istniejacy_oddzial(string lokalizacja);
void dodaj_nowy_oddzial(string lokalizacja);
void dodaj_samochod_do_oddzialu(string lokalizacja);
void usun_samochod_z_oddzialu(string lokalizacja);
int wybor_opcji(void);
void SYMULUJ(int liczba_cykli);

int main()
{
	instrukcja_1();
	Sleep(15000);
	system("CLS");
	//blok z przykladowymi danymi
	{
		string przykladowe_oddzialy[4] = {"Wesola", "Siedlce", "Lublin", "Poznan"};

		string przykladowi_klienci[8][4] = {
			{"Kowalski","Radoslaw","Wesola","Sikorskiego2"},
			{"Cichy","Kamil","Lublin","Gorzysta5"},
			{"Marny","Pawel","Poznan","Jezioranskiego1"},
			{"Mruczek","Marian","Siedlce","Robocza4"},
			{"Jeczala","Adrianna","Wesola","Stocha2"},
			{"Klaczek","Kunegunda","Siedlce","krucha4"},
			{"Parzydlo","Anna","Lublin","Rekina2"},
			{"Modny","Bartek","Poznan","Rubinowa4"}
		};

		cout<<"Wprowadzanie przykladowych danych...\n";
		Sleep(1000);

		for(int i=0; i<4; i++)
		{
			dodaj_nowy_oddzial(przykladowe_oddzialy[i]);
			Sleep(1000);
			dodaj_samochod_do_oddzialu(przykladowe_oddzialy[i]);
			Sleep(1000);
		}

		for(int i=0; i<4; i++)
		{
			baza_firmy.dodaj_samochod();
			Sleep(1000);
		}

		for(int i=0; i<8;i++)
		{
			baza_firmy.dodaj_klienta(przykladowi_klienci[i]);
			Sleep(1000);
		}
	}

	Sleep(1000);

	string lokalizacja;
	string dane_klienta[4];
	int liczba_cykli;

	system("CLS");
	instrukcja_2();

	while(true)
	{
		int opcja = wybor_opcji();

		system("CLS");

		//zaleznie od wybranej opcji realizowane sa rozne polecenia
		switch(opcja)
		{
		case 0: instrukcja_2(); break;

		case 1: podstawowe_informacje_o_firmie(); break;

		case 2: informacje_o_stanie_klientow(); break;

		case 3: informacje_o_samochodach_firmy(); break;

		case 4: informacje_o_samochodach_bazy(); break;

		case 5: cout<<"Prosze wpisac lokalizacje oddzialu.\n";
				cin>>lokalizacja;
				informacje_o_samochodach_oddzialu(lokalizacja); break;

		case 6: cout<<"Prosze wpisac lokalizacje nowego oddzialu.\n";
				cin>>lokalizacja;
				dodaj_nowy_oddzial(lokalizacja); break;

		case 7: cout<<"Prosze wpisac lokalizacje oddzialu do usuniecia.\n";
				cin>>lokalizacja;
				usun_istniejacy_oddzial(lokalizacja); break;

		case 8: cout<<"Prosze wpisac dane klienta do dodania w kolejnosci: \n";
				cout<<"NAZWISKO-IMIE-LOKALIZACJA-ADRES\n";
				for(int i=0; i<4; i++)
					cin>>dane_klienta[i];
				std::cin.sync();
				baza_firmy.dodaj_klienta(dane_klienta); break;

		case 9: cout<<"Prosze wpisac dane klienta do usuniecia w kolejnosci: \n";
				cout<<"NAZWISKO-IMIE-LOKALIZACJA-ADRES\n";
				for(int i=0; i<4; i++)
					cin>>dane_klienta[i];
				std::cin.sync();
				baza_firmy.usun_klienta(dane_klienta); break;

		case 10: baza_firmy.dodaj_samochod(); break;

		case 11: baza_firmy.usun_samochod(); break;

		case 12: cout<<"Prosze podac lokalizacje oddzialu do ktorego dodany zostanie samochod.\n";
				cin>>lokalizacja;
				dodaj_samochod_do_oddzialu(lokalizacja); break;

		case 13: cout<<"Prosze podac lokalizacje oddzialu z ktorego usuniety zostanie samochod.\n";
				cin>>lokalizacja;
				usun_samochod_z_oddzialu(lokalizacja); break;

		case 14: cout<<"Podaj liczbe cykli, przez ktore ma trwac symulacja.\n";
				 cin>>liczba_cykli;
				 while(!cin.good())
				 {
					 cout<<"Bledne dane. Prosze ponownie wpisac liczbe cykli.\n";
					 cin.clear();
					 cin.sync();
					 cin>>liczba_cykli;
				 }
				 cin.sync();

				 plik_wynikowy.open("wynik_symulacji.txt");

				 SYMULUJ(liczba_cykli);

				 plik_wynikowy.close();

				 cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
				 cout<<"Symulacja zakonczona pomyslnie. Wynik symulacji znajduje sie w pliku wynikowym.\n";
				 cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
				 return 0;
		}
		
		cout<<"Prosze wprowadzic nowe polecenie\n";
		cout<<"Aby ponownie zobaczyc instrukcje wcisnij 0.\n";
	}
}

//funkcja zwracajaca wybrana przez urzytkownika opcje
int wybor_opcji(void)
{
	int wybor;
	cin>>wybor;
	while(!cin.good() || wybor<0 || wybor >14)
	{
		cin.clear();
		cin.sync();
		cout<<"Prosze ponownie wpisac numer polecenia.\n";
		cin>>wybor;
	}
	cin.sync();
	return wybor;
}

//wyswietlenie instrukcji 1
void instrukcja_1(void)
{	
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";
	cout<<"\t\tWITAJ W SYMULATORZE DZIALANIA FIRMY KURIERSKIEJ\n\n";
	cout<<"W programie tym mozesz:\n";
	cout<<"- dodawac i usuwac oddzialy firmy podajac ich lokalizacje;\n";
	cout<<"- dodawac i usuwac samochody w poszczegolnych oddzialach oraz w bazie;\n";
	cout<<"- dodawac i usuwac klientow firmy, podajac ich dane;\n";
	cout<<"Oraz przeprowadzic symulacje firmy z podanymi parametrami.\n\n";
	cout<<"UWAGA, warunek dodania klienta:\n";
	cout<<"istnieje oddzial o tej samej lokalizacji co lokalizacja klienta.\n";
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";
}

//wyswietlenie instrukcji 2
void instrukcja_2(void)
{
	cout<<"**---------------------------------------------------------------------------**\n";
	cout<<"\t\tWYSWIETLANIE INFORMACJI\n";
	cout<<"1) Podstawowe informacje o firmie;\n";
	cout<<"2) Informacje o stanie klientow;\n";
	cout<<"3) Informacje o samochodach obslugujacych firme;\n";
	cout<<"4) Informacje o samochodach obslugujacych baze;\n";
	cout<<"5) Informacje o samochodach obslugujacych konkretny oddzial;\n";
	cout<<"**---------------------------------------------------------------------------**\n";
	cout<<"\t\tZMIANA PARAMETROW FIRMY\n";
	cout<<"6) Dodaj nowy oddzial;\n";
	cout<<"7) Usun istniejacy oddzial;\n";
	cout<<"8) Dodaj nowego klienta;\n";
	cout<<"9) Usun istniejacego klienta;\n";
	cout<<"10) Dodaj samochod do bazy;\n";
	cout<<"11) Usun samochod z bazy;\n";
	cout<<"12) Dodaj samochod do oddzialu;\n";
	cout<<"13) Usun samochod z oddzialu.\n";
	cout<<"**---------------------------------------------------------------------------**\n";
	cout<<"14)\t\tROZPOCZNIJ SYMULACJE\n";
	cout<<"**---------------------------------------------------------------------------**\n";
}

//wyswietlenie podstawowych informacji o firmie
void podstawowe_informacje_o_firmie(void)
{
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	cout<<"Nazwa firmy: ToMpAcZkA symulator\n";
	cout<<"Lokalizacja bazy: Warszawa\n";
	cout<<"Ilosc oddzialow: "<<wektor_oddzialow.size()<<endl;
	cout<<"Lokalizacje oddzialow: ";
	if(wektor_oddzialow.empty())
		cout<<"brak oddzialow";
	else
	{
		for(unsigned i=0; i<wektor_oddzialow.size(); i++)
			cout<<wektor_oddzialow[i]->zwroc_lokalizacje()<<" ";
	}
	cout<<endl;
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
}

//wyswietlenie informacji o stanie klientow
void informacje_o_stanie_klientow(void)
{
	int ilosc_klientow = baza_firmy.liczba_klientow();
	if(ilosc_klientow == 0)
	{
		cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
		cout<<"Firma aktualnie nie ma klientow.\n";
		cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	}
	else
	{
		cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
		cout<<"Aktualna liczba klientow: "<<ilosc_klientow<<endl;
		baza_firmy.wyswietl_klientow();
		cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	}
}

//wyswietlenie informacji o samochodach obslugujacych firme
void informacje_o_samochodach_firmy(void)
{
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	cout<<"Firma jest obslugiwana przez 3 rodzaje samochodow:\n";
	cout<<endl;
	Ford_Transist::Ford_Transist_informacje();
	cout<<endl;
	Renault_Master::Renault_Master_informacje();
	cout<<endl;
	Volkswagen_Caddy::Volkswagen_Caddy_informacje();
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
}

//wyswietlenie informacji o samochodach obslugujacych baze
void informacje_o_samochodach_bazy(void)
{
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	cout<<"Stan samochodow w bazie:\n";
	baza_firmy.wyswietl_stan_samochodow();
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
}

//wyswietlenie informacji o samochodach obslugujacych wybrany oddzial
void informacje_o_samochodach_oddzialu(string lokalizacja)
{
	for(unsigned i=0; i<wektor_oddzialow.size(); i++)
	{
		if(wektor_oddzialow[i]->zwroc_lokalizacje() == lokalizacja)
		{
			cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			cout<<"Stan samochodow w oddziale "<<lokalizacja<<endl;
			wektor_oddzialow[i]->wyswietl_stan_samochodow();
			cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			return;
		}
	}
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	cout<<"Oddzial o podanej lokalizacji nie istnieje.\n";
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
}

//funkcja dodajaca nowy oddzial
void dodaj_nowy_oddzial(string lokalizacja)
{
	for(unsigned i=0; i< wektor_oddzialow.size(); i++)
	{
		if(lokalizacja == wektor_oddzialow[i]->zwroc_lokalizacje())
		{
			cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			cout<<"Oddzial o podanej lokalizacji: "<<lokalizacja<<" juz istnieje.\n";
			cout<<"Stworzenie kolejnego jest niemozliwe.\n";
			cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			return;
		}
	}

	Oddzial *nowy_oddzial = new Oddzial(lokalizacja);
	wektor_oddzialow.push_back(nowy_oddzial);
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	cout<<"Oddzial: "<<lokalizacja<<" zostal dodany.\n";
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
}

//funkcja usuwajaca istniejacy oddzial
void usun_istniejacy_oddzial(string lokalizacja)
{
	for(unsigned i=0; i<wektor_oddzialow.size(); i++)
	{
		if(lokalizacja == wektor_oddzialow[i]->zwroc_lokalizacje())
		{
			Oddzial * to_kill = wektor_oddzialow[i];

			if(i == wektor_oddzialow.size() - 1)
				wektor_oddzialow.pop_back();
			else
				wektor_oddzialow.erase(wektor_oddzialow.begin()+i);
			delete to_kill;

			cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			cout<<"Oddzial "<<lokalizacja<<" zostal usuniety.\n";
			cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			baza_firmy.usun_nieaktualnych_klientow();
			return;
		}
	}
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	cout<<"Oddzial o podanej lokalizacji: "<<lokalizacja<<" nie istnieje.\n";
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
}

//funkcja didajaca samochod do oddzialu
void dodaj_samochod_do_oddzialu(string lokalizacja)
{
	for(unsigned i=0; i<wektor_oddzialow.size(); i++)
	{
		if(wektor_oddzialow[i]->zwroc_lokalizacje() == lokalizacja)
		{
			wektor_oddzialow[i]->dodaj_samochod();
			return;
		}
	}
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	cout<<"Oddzial o podanej lokalizacji nie istnieje.\n";
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
}

//funkcja usuwajaca samochod z oddzialu
void usun_samochod_z_oddzialu(string lokalizacja)
{
	for(unsigned i=0; i<wektor_oddzialow.size(); i++)
	{
		if(wektor_oddzialow[i]->zwroc_lokalizacje() == lokalizacja)
		{
			wektor_oddzialow[i]->usun_samochod();
			return;
		}
	}
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	cout<<"Oddzial o podanej lokalizacji nie istnieje.\n";
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
}

//funkcja przeprowadzajaca symulacje dzialania firmy
void SYMULUJ(int liczba_cykli)
{
	for(int i=0; i<liczba_cykli; i++)
	{
		system("CLS");
		cout<<"-----------------------------------SYMULACJA-----------------------------------\n";
		baza_firmy.generuj_przesylki();
		baza_firmy.rozwoz_przesylki_z_bazy();
		for(unsigned i=0; i<wektor_oddzialow.size(); i++)
			wektor_oddzialow[i]->rozwoz_przesylki_z_oddzialu();

		Sleep(6000);
		system("CLS");

		cout<<"-----------------------------------SYMULACJA-----------------------------------\n";
		cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
		cout<<"\t\tAKTUALNE KOLEJKI W ODDZIALACH\n";
		for(unsigned i=0; i<wektor_oddzialow.size(); i++)
			cout<<"\t\t"<<wektor_oddzialow[i]->zwroc_lokalizacje()<<": "<<wektor_oddzialow[i]->wyswietl_liczbe_przesylek()<<endl;
		cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";

		if(plik_wynikowy.is_open())
		{
			plik_wynikowy<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			plik_wynikowy<<"\t\tAKTUALNE KOLEJKI W ODDZIALACH\n";
			for(unsigned i=0; i<wektor_oddzialow.size(); i++)
				plik_wynikowy<<"\t\t"<<wektor_oddzialow[i]->zwroc_lokalizacje()<<": "<<wektor_oddzialow[i]->wyswietl_liczbe_przesylek()<<endl;
			plik_wynikowy<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
		}
		Sleep(6000);
	}
}

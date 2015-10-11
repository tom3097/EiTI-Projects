//Projekt nr 2: klasa reprezentujaca zbior macierzy 3x3 typu float
//Przygotowal: Tomasz Bochenski

#include "zbior.h"

//tworzenie struktury ktora posluzy do stworzenia listy zbiorow
struct lista_zbiorow
{
	zbior wartosc;
	lista_zbiorow *nastepny;
};

//wskaznik na poczatek listy
lista_zbiorow *head = NULL;
//wskazniki na dwa wybrane zbiory na ktorych przeprowadzane sa operacje
lista_zbiorow *pierwszy_wybrany, *drugi_wybrany;
//pomocnicza tablica w ktorej pcherzowywana bedzie macierz 3x3 przed ewentualnym dodaniem
float tablica_pomocnicza[3][3];

//wyswietlanie instrukcji
void instrukcja(void);
//dodawanie zbioru
void dodaj_zbior(void);
//dodawanie elementu do zbioru
void dodaj_element_zbioru(void);
//usuwanie elementu ze zbioru
void usun_element_zbioru(void);
//usuwanie calego zbioru
void usun_zbior(void);
//sprawdzanie czy zbiory sa rowne
void sprawdz_rownosc(void);
//sprawdzanie czy zbiory nie sa rowne
void sprawdz_nierownosc(void);
//oblicza sume zbiorow
void oblicz_sume_zbiorow(void);
//oblicza iloczyn zbiorow
void oblicz_iloczyn_zbiorow(void);
//wypisuje podany zbior
void drukuj_zawartosc_zbioru(void);
//funkcja odpowiedzialan za poprawny wybor numeru reprezentujacego dzialanie, ktore chce sie przeprowadzic
int wybor_opcji(void);
//odpowiedzialan za pobranie prawidlowego numeru zbioru
int wybor_zbioru(void);
//wybiera 2 zbiory na ktorych przeprowadzana jest operacja
void wybierz_zbiory(void);
//tworzy element zbioru (macierz 3x3), zwraca true gdy tworzenie bylo poprawne i false gdy nie
bool stworz_element(void);
//przeszukuje liste i zwraca wskaznik na konkretny zbior
lista_zbiorow * znajdz_zbior(int numer_zbioru);

int main()
{
	instrukcja();
	while(true)
	{
		cout<<"Aby ponownie wyswietlic instrukcje wcisnij 0.\n";
		int opcja = wybor_opcji();
		switch(opcja)
		{
		case 0: instrukcja(); break;
		case 1: dodaj_zbior(); break;
		case 2: dodaj_element_zbioru(); break;
		case 3: usun_element_zbioru(); break;
		case 4: usun_zbior(); break;
		case 5: sprawdz_rownosc(); break;
		case 6: sprawdz_nierownosc(); break;
		case 7: oblicz_sume_zbiorow(); break;
		case 8: oblicz_iloczyn_zbiorow(); break;
		case 9: drukuj_zawartosc_zbioru(); break;
		case 10: exit(0);
		}
		cout<<"Wybierz kolejna opcje.\n";
	}
	return 0;
}

void instrukcja(void)
{
	cout<<"------------------------------------------------------------------------------"<<endl;
	cout<<"1) Dodaj zbior;\t\t\t\t2) Dodaj element zbioru;"<<endl;
	cout<<"3) Usun element zbioru;\t\t\t4) Usun zbior;"<<endl;
	cout<<"5) Sprawdz rownosc;\t\t\t6) Sprawdz nierownosc;"<<endl;
	cout<<"7) Oblicz sume zbiorow;\t\t\t8) Oblicz iloczyn zbiorow;"<<endl;
	cout<<"9) Drukuj zawartosc zbioru;\t\t10) Zakoncz program."<<endl;
	cout<<"Aktualna liczba zbiorow to: "<<zbior::zwroc_liczbe_obiektow()<<endl;
	cout<<"------------------------------------------------------------------------------"<<endl;
}

void dodaj_zbior(void)
{
	lista_zbiorow *aktualny = new lista_zbiorow;
	aktualny->nastepny = NULL;

	if(head == NULL)
		head = aktualny;
	else
	{
		lista_zbiorow *tmp = head;
		while(tmp->nastepny != NULL)
			tmp = tmp->nastepny;
		tmp->nastepny = aktualny;
	}
	cout<<"------------------------------------------------------------------------------"<<endl;
	cout<<"\tDodawanie zbioru zakonczone.\n";
	cout<<"Aktualna liczba zbiorow to: "<<zbior::zwroc_liczbe_obiektow()<<endl;
	cout<<"------------------------------------------------------------------------------"<<endl;
}

void dodaj_element_zbioru(void)
{
	//w przypadku gdy zaden zbior nie istnieje nie mozna dodawac elementow
	if(zbior::zwroc_liczbe_obiektow() == 0)
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tBrak zbiorow. Najpierw musisz dodac zbior.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
		return;
	}
	//gdy element stworzno poprawnie mozliwe jest jego dodanie
	if(stworz_element() == true)
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tMacierz uzupelniona poprawnie.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
		Macierze_3x3<float> macierz_do_dodania(tablica_pomocnicza);
		cout<<"Podaj numer zbioru do ktorego chcesz dodac element.\n";
		cout<<"Aktualna liczba zbiorow to: "<<zbior::zwroc_liczbe_obiektow()<<endl;
		int numer = wybor_zbioru();
		lista_zbiorow *wybrany = znajdz_zbior(numer);
		wybrany->wartosc.dodaj_element_warunkowo(macierz_do_dodania);
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tDodawanie zakonczono pomyslnie.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
	}
	//gdy funkcja stworz_element zwrocila false element nie jest dodawany
	else
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tMacierz nie zostala uzupelniona poprawnie.\nNie moze zostac dodana do zbioru.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
	}
}

void usun_element_zbioru(void)
{
	//w przypadku gdy zaden zbior nie istieje nie mozna usuwac elementow
	if(zbior::zwroc_liczbe_obiektow() == 0)
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tBrak zbiorow. Najpierw musisz dodac zbior.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
		return;
	}
	cout<<"Podaj numer zbioru z ktorego chcesz usunac element.\n";
	cout<<"Aktualna liczba zbiorow to: "<<zbior::zwroc_liczbe_obiektow()<<endl;
	int numer = wybor_zbioru();
	lista_zbiorow *wybrany = znajdz_zbior(numer);
	int numer_macierzy;
	cout<<"Podaj numer macierzy ktora ma zostac usunieta ze zbioru.\n";
	cout<<"W wyniku podania numeru ktory nie istnieje nic nie zostanie usunieta.\n";
	cin>>numer_macierzy;
	while(!cin.good())
	{
		cin.clear();
		cin.sync();
		cin>>numer_macierzy;
	}
	wybrany->wartosc.usun_element(numer_macierzy);
	cout<<"------------------------------------------------------------------------------"<<endl;
	cout<<"\tUsuwanie elementu zakonczone.\n";
	cout<<"------------------------------------------------------------------------------"<<endl;
}

void usun_zbior(void)
{
	//w przypadku gdy zaden zbior nie istnieje nie mozna usuwac zbiorow
	if(zbior::zwroc_liczbe_obiektow() == 0)
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tBrak zbiorow. Najpierw musisz dodac zbior.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
		return;
	}
	cout<<"Podaj numer zbioru ktory chcesz usunac.\n";
	cout<<"Aktualna liczba zbiorow to: "<<zbior::zwroc_liczbe_obiektow()<<endl;
	int numer_zbioru = wybor_zbioru();
	lista_zbiorow *to_kill = head;
	lista_zbiorow * poprzedni;
	for(int i=1; i<numer_zbioru; i++)
	{
		poprzedni = to_kill;
		to_kill = to_kill->nastepny;
	}
	if(to_kill = head)
	{
		head = head->nastepny;
		delete to_kill;
	}
	else
	{
		poprzedni->nastepny = to_kill->nastepny;
		delete to_kill;
	}
	cout<<"------------------------------------------------------------------------------"<<endl;
	cout<<"\tUsuwanie zbioru zakonczone.\n";
	cout<<"------------------------------------------------------------------------------"<<endl;
}

void sprawdz_rownosc(void)
{
	//w przypadku gdy zaden zbior nie istieje nie da sie sprawdzic rownosci zbiorow
	if(zbior::zwroc_liczbe_obiektow() == 0)
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tBrak zbiorow. Najpierw musisz dodac zbior.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
		return;
	}
	wybierz_zbiory();
	if(pierwszy_wybrany->wartosc == drugi_wybrany->wartosc)
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tRownosc prawdziwa, zbiory sa rowne.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
	}
	else
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tRownosc nieprawdziwa, zbiory nie sa rowne.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
	}
}

void sprawdz_nierownosc(void)
{
	//w przypadku gdy zaden zbior nie istieje nie da sie sprawdzic nierownosci zbiorow
	if(zbior::zwroc_liczbe_obiektow() == 0)
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tBrak zbiorow. Najpierw musisz dodac zbior.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
		return;
	}
	wybierz_zbiory();
	if(pierwszy_wybrany->wartosc != drugi_wybrany->wartosc)
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tNierownosc prawdziwa, zbiory nie sa rowne.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
	}
	else
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tNierownosc nieprawdziwa, zbiory sa rowne.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
	}
}

void oblicz_sume_zbiorow(void)
{
	//w przypadku gdy zaden zbior nie istnieje nie da sie obliczyc sumy zbiorow
	if(zbior::zwroc_liczbe_obiektow() == 0)
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tBrak zbiorow. Najpierw musisz dodac zbior.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
		return;
	}
	wybierz_zbiory();
	zbior wynik = pierwszy_wybrany->wartosc + drugi_wybrany->wartosc;
	cout<<"------------------------------------------------------------------------------"<<endl;
	cout<<"\tSuma zbiorow to:\n";
	cout<<wynik;
	cout<<"------------------------------------------------------------------------------"<<endl;
}

void oblicz_iloczyn_zbiorow(void)
{
	//w przypadku braku zbiorow nie da sie obliczyc iloczynu zbiorow
	if(zbior::zwroc_liczbe_obiektow() == 0)
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tBrak zbiorow. Najpierw musisz dodac zbior.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
		return;
	}
	wybierz_zbiory();
	zbior wynik = pierwszy_wybrany->wartosc * drugi_wybrany->wartosc;
	cout<<"------------------------------------------------------------------------------"<<endl;
	cout<<"\tIloczyn zbiorow to:\n";
	cout<<wynik;
	cout<<"------------------------------------------------------------------------------"<<endl;
}

void drukuj_zawartosc_zbioru(void)
{
	//w przypadku braku zbiorownie da sie ich wyswietlic
	if(zbior::zwroc_liczbe_obiektow() == 0)
	{
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"\tBrak zbiorow. Najpierw musisz dodac zbior.\n";
		cout<<"------------------------------------------------------------------------------"<<endl;
		return;
	}
	cout<<"Podaj numer zbioru ktory chcesz zobaczyc.\n";
	cout<<"Aktualna liczba zbiorow to: "<<zbior::zwroc_liczbe_obiektow()<<endl;
	int numer = wybor_zbioru();
	lista_zbiorow *wybrany = znajdz_zbior(numer);
	cout<<"------------------------------------------------------------------------------"<<endl;
	cout<<"Podany zbior sklada sie z:\n";
	cout<<wybrany->wartosc;
	cout<<"------------------------------------------------------------------------------"<<endl;
}

void wybierz_zbiory(void)
{
	int numer;
	cout<<"Aktualna liczba zbiorow to: "<<zbior::zwroc_liczbe_obiektow()<<endl;
	cout<<"Podaj numer pierwszego zbioru.\n";
	numer = wybor_zbioru();
	pierwszy_wybrany = znajdz_zbior(numer);
	cout<<"Podaj numer drugiego zbioru.\n";
	numer = wybor_zbioru();
	drugi_wybrany = znajdz_zbior(numer);
}

int wybor_opcji(void)
{
	int opcja;
	cin>>opcja;
	while(!cin.good() || opcja>10 || opcja <0)
	{
		cout<<"Wpisono niedozwolone znaki.\nProsze ponownie wpisac odpowiednia cygre.\n";
		if(!cin.good())
		{
			cin.clear();
			cin.sync();
		}
	cin>>opcja;
	}
	cin.sync();
	return opcja;
}

int wybor_zbioru(void)
{
	int numer;
	cin>>numer;
	while(!cin.good() || numer > zbior::zwroc_liczbe_obiektow() || numer <1)
	{
		cout<<"Niepoprawny wybor.\nProsze podac numer jeszcze raz.\n";
		if(!cin.good())
		{
			cin.clear();
			cin.sync();
		}
		cin>>numer;
	}
	cin.sync();
	return numer;
}

lista_zbiorow * znajdz_zbior(int numer_zbioru)
{
	lista_zbiorow *tmp = head;
	for(int i=1; i<numer_zbioru; i++)
		tmp = tmp->nastepny;
	return tmp;
}

bool stworz_element(void)
{
	cout<<"Podaj macierz 3x3 ktora chcesz dodac jako element.\n";
	bool poprawne = true;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			cin>>tablica_pomocnicza[i][j];
			if(!cin.good())
			{
				poprawne = false;
				break;
			}
		}
		if(poprawne == false)
		break;
	}
	cin.clear();
	cin.sync();
	return poprawne;
}

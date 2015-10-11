//Projekt nr 2: klasa reprezentujaca zbior macierzy 3x3 typu float
//Przygotowal: Tomasz Bochenski

#include "zbior.h"
#define POKAZ_KOMUNIKATY_ZBIORY false

//ustawienie poczatkowej liczby obiektow na 0
int zbior::ilosc_obiektow = 0;

//konstruktor domyslny
zbior::zbior()
{
	if(POKAZ_KOMUNIKATY_ZBIORY == true)
		cout<<"Uruchomiono konstruktor domyslny klasy ZBIOR.\n";
	ilosc_obiektow++;
	liczba_elementow_zbioru = 0;
	poczatek = NULL;
}

//konstruktor kopiujacy
zbior::zbior(const zbior &obiekt)
{	
	if(POKAZ_KOMUNIKATY_ZBIORY == true)
		cout<<"Uruchomiono konstruktor kopiujacy klasy ZBIOR.\n";
	ilosc_obiektow++;
	liczba_elementow_zbioru = 0;
	poczatek = NULL;
	element *tmp = obiekt.poczatek;

	while(tmp != NULL)
	{
		//bo wiemy ze elementy w zbiorze ktory "kopiujemy" nie powtarzaja sie
		dodaj_element_bezwarunkowo(tmp->macierz_float);
		tmp= tmp->nastepny;
	}
}

//bezwarunkowe dodawanie elementu
void zbior::dodaj_element_bezwarunkowo(const Macierze_3x3<float> &macierz)
{
	liczba_elementow_zbioru++;
	element *aktualny = new element;
	aktualny->macierz_float = macierz;
	aktualny->nastepny = NULL;
	if(poczatek == NULL)
		poczatek = aktualny;
	else
	{
		element *tmp = poczatek;
		while(tmp->nastepny!= NULL)
			tmp = tmp->nastepny;
		tmp->nastepny = aktualny;
	}
}

//warunkowe dodawanie elementu
void zbior::dodaj_element_warunkowo(const Macierze_3x3<float> &macierz)
{
	//gdy podanej macierzy nie ma w zbiorze wywolujemy funkcje dodaj_element_bezwarunkowo
	//w przeciwnym przypadku macierz nie jest dodawana
	if(czy_istnieje(macierz) == false)
		dodaj_element_bezwarunkowo(macierz);
}

//usuwanie elementu
void zbior::usun_element(int numer_macierzy)
{
	//gdy podany numer macierzy jest bledny usuwanie nie zostanie wykonane
	if(numer_macierzy > liczba_elementow_zbioru || numer_macierzy<1)
		return;
	//znajdywanie i usuwanie wybranego elementu
	liczba_elementow_zbioru--;
	element *to_kill = poczatek;
	element *poprzedni;
	for(int i=1; i<numer_macierzy; i++)
	{
		poprzedni = to_kill;
		to_kill = to_kill->nastepny;
	}

	if(to_kill == poczatek)
	{
		poczatek = poczatek->nastepny;
		delete to_kill;
	}
	else
	{
		poprzedni->nastepny = to_kill->nastepny;
		delete to_kill;
	}
}

bool zbior::czy_istnieje(const Macierze_3x3<float> &macierz)const
{
	bool wynik = false;
	element *tmp = poczatek;
	while(tmp != NULL)
	{
		if(macierz == tmp->macierz_float)
		{
			wynik = true;
			break;
		}
		tmp = tmp->nastepny;
	}
	return wynik;
}

//destruktor
zbior::~zbior()
{
	if(POKAZ_KOMUNIKATY_ZBIORY == true)
		cout<<"Uruchomiono destruktor klasy ZBIOR.\n";
	ilosc_obiektow--;
	element *tmp, *to_kill;
	to_kill = poczatek;
	//usuwanie alokowanych dynamicznie elementow zbioru
	while(to_kill != NULL)
	{
		tmp = to_kill->nastepny;
		delete to_kill;
		to_kill = tmp;
	}
}

//przeciazenie operatora =
zbior & zbior::operator=(const zbior &obiekt)
{
	if(POKAZ_KOMUNIKATY_ZBIORY == true)
		cout<<"Uruchomiono metode kopiowania zbioru.\n";
	//gdy chcemy przypisac obiektowi zbior jego samego
	if(this == &obiekt)
		return *this;

	//usuwanie dotychczasowych elementow
	element *tmp, *to_kill;
	to_kill = poczatek;
	while(to_kill != NULL)
	{
		tmp = to_kill->nastepny;
		delete to_kill;
		to_kill = tmp;
	}

	//dodawanie nowych elementow
	poczatek = NULL;
	liczba_elementow_zbioru = 0;

	tmp = obiekt.poczatek;
	while(tmp != NULL)
	{
		dodaj_element_bezwarunkowo(tmp->macierz_float);
		tmp= tmp->nastepny;
	}
	return *this;
}

//przeciazenie operatora drukowania
ostream& operator << (ostream &wyjscie, const zbior &obiekt)
{
	if(POKAZ_KOMUNIKATY_ZBIORY == true)
		cout<<"Uruchomiono metode drukujaca zawartosc zbioru.\n";
	zbior::element * tmp = obiekt.poczatek;
	if(tmp == NULL)
		wyjscie<<"Zbior jest pusty.\n";
	else
	{
		int numer = 1;
		while(tmp != NULL)
		{
			wyjscie<<"Macierz numer:"<<numer<<endl;
			wyjscie<<tmp->macierz_float<<endl;
			tmp = tmp->nastepny;
			numer++;
		}
	}
	return wyjscie;
}

//przeciazenie operatora porownania
bool zbior::operator==(const zbior &obiekt)const
{
	if(POKAZ_KOMUNIKATY_ZBIORY == true)
		cout<<"Uruchomiono metode porownujaca zbiory.\n";
	//jesli zbiory maja rozna liczbe elementow to nie sa rowne
	if(liczba_elementow_zbioru != obiekt.liczba_elementow_zbioru)
		return false;

	element *tmp = obiekt.poczatek;
	while(tmp != NULL)
	{
		//jesli zbiory maja taka sama liczbe elementow
		//i dla kazdej macierzy ze zbioru A istnieje identyczna w zbiorze B to zbiory te sa rowne
		if(czy_istnieje(tmp->macierz_float) == false)
			return false;
		tmp = tmp->nastepny;
	}
	return true;
}

//przeciazenie operatora nierownosci
bool zbior::operator!=(const zbior &obiekt)const
{
	if(POKAZ_KOMUNIKATY_ZBIORY == true)
		cout<<"Uruchomiono metode porownujaca zbiory.\n";
	//zwraca zanegowana wartosc zwrocona przez operator ==
	return !(*this == obiekt);
}

//przeciazenie operatora dodawania (suma zbiorow)
zbior zbior::operator+(const zbior &obiekt)const
{
	if(POKAZ_KOMUNIKATY_ZBIORY == true)
		cout<<"Uruchomiono metode obliczajaca sume zbiorow.\n";
	zbior wynik;
	//przypisuje jeden z sumowanych zbiorow zbiorowi wynik
	wynik = *this;
	element *tmp = obiekt.poczatek;

	while(tmp != NULL)
	{
		//dodaje do zbioru wynik kolejne elementy (macierze) pod warunkiem ze jeszcze ich tam nie ma
		wynik.dodaj_element_warunkowo(tmp->macierz_float);
		tmp= tmp->nastepny;
	}
	return wynik;
}

//przeciazenie operatora mnozenia (iloczyn zbiorow)
zbior zbior::operator*(const zbior &obiekt)const
{
	if(POKAZ_KOMUNIKATY_ZBIORY == true)
		cout<<"Uruchomiono metode obliczajaca iloczyn zbiorow.\n";
	zbior wynik;
	element *tmp = obiekt.poczatek;
	//przeglada kazdy element ze zbioru B i sprawdza czy identyczny istnieje w zbiorze A
	//gdy element istnieje zarowno w A i B, jest on dodawany bezwarunkowo do obiektu wynik
	while(tmp != NULL)
	{
		if(czy_istnieje(tmp->macierz_float) == true)
			wynik.dodaj_element_bezwarunkowo(tmp->macierz_float);
		tmp = tmp->nastepny;
	}
	return wynik;
}





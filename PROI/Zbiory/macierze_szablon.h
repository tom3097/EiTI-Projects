//Projekt nr 2: klasa reprezentujaca zbior macierzy 3x3 typu float
//Przygotowal: Tomasz Bochenski

#ifndef MACIERZE_SZABLON_H_
#define MACIERZE_SZABLON_H_
#include <iostream>
#include <cstring>
#include <string>
#define POKAZ_KOMUNIKATY_MACIERZE false

using namespace std;

template <class Type>
class Macierze_3x3
{
    private:
        Type m_macierz[3][3];
    public:
        Macierze_3x3(Type tablica[3][3]);
        Macierze_3x3();
        ~Macierze_3x3();
        Macierze_3x3 operator+(const Macierze_3x3 &obiekt)const;
        void operator+=(const Macierze_3x3 &obiekt);
        Macierze_3x3 operator-(const Macierze_3x3 &obiekt)const;
        void operator-=(const Macierze_3x3 &obiekt);
        Macierze_3x3 operator*(const Macierze_3x3 &obiekt)const;
        void operator*=(const Macierze_3x3 &obiekt);
        double oblicz_wyznacznik(void);
		bool operator==(const Macierze_3x3 &obiekt)const;
		//funkcja zaprzyjazniona, nawiasy <> w deklaracji pozwalaja zidentyfikowac ja jako specjalizacje szablonu
        friend ostream & operator<< <>(ostream &wyjscie,const Macierze_3x3 &obiekt);
};


//konstruktor
template <class Type>
Macierze_3x3<Type>::Macierze_3x3(Type tablica[3][3])
{
    if(POKAZ_KOMUNIKATY_MACIERZE == true)
        cout<<"Uruchomiono konstruktor z parametrem klasy MACIERZE_3x3.\n";
    memcpy(m_macierz,tablica,9*sizeof(Type));
}

//konstruktor domyslny
template <class Type>
Macierze_3x3<Type>::Macierze_3x3()
{
    if(POKAZ_KOMUNIKATY_MACIERZE == true)
        cout<<"Uruchomiono konstruktor domyslny klasy MACIERZE_3x3.\n";
    memset(m_macierz,0,9*sizeof(Type));
}

//destruktor
template <class Type>
Macierze_3x3<Type>::~Macierze_3x3()
{
    if(POKAZ_KOMUNIKATY_MACIERZE == true)
        cout<<"Uruchomiono destruktor klasy MACIERZE_3x3.\n";
}

//przeciazenie operatora +
template <class Type>
Macierze_3x3<Type> Macierze_3x3<Type>::operator+(const Macierze_3x3<Type> &obiekt)const
{
    if(POKAZ_KOMUNIKATY_MACIERZE == true)
        cout<<"Uruchomiono metode dodajaca macierze (przeciazenie operatora: +).\n";
    Macierze_3x3<Type> wynik;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            wynik.m_macierz[i][j] = m_macierz[i][j] + obiekt.m_macierz[i][j];
    return wynik;
}

//przeciazenie operatora +=
template <class Type>
void Macierze_3x3<Type>::operator+=(const Macierze_3x3<Type> &obiekt)
{
	if(POKAZ_KOMUNIKATY_MACIERZE == true)
        cout<<"Uruchomiono metode dodajaca macierze (przeciazenie operatora: +=).\n";
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            m_macierz[i][j] += obiekt.m_macierz[i][j];
}

//przeciazenie operatora -
template <class Type>
Macierze_3x3<Type> Macierze_3x3<Type>::operator-(const Macierze_3x3<Type> &obiekt)const
{
	if(POKAZ_KOMUNIKATY_MACIERZE == true)
        cout<<"Uruchomiono metode odejmujaca macierze (przeciazenie operatora: -).\n";
    Macierze_3x3<Type> wynik;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            wynik.m_macierz[i][j] = m_macierz[i][j] - obiekt.m_macierz[i][j];
    return wynik;
}

//przeciazenie operatora -=
template <class Type>
void Macierze_3x3<Type>::operator-=(const Macierze_3x3<Type> &obiekt)
{
    if(POKAZ_KOMUNIKATY_MACIERZE == true)
        cout<<"Uruchomiono metode odejmujaca macierze (przeciazenie operatora: -=).\n";
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            m_macierz[i][j] -= obiekt.m_macierz[i][j];
}

//przeciazenie operatora *
template <class Type>
Macierze_3x3<Type> Macierze_3x3<Type>::operator*(const Macierze_3x3<Type> &obiekt)const
{
    if(POKAZ_KOMUNIKATY_MACIERZE == true)
        cout<<"Uruchomiono metode mnozaca macierze (przeciazenie operatora: *).\n";
    Macierze_3x3<Type> wynik;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            Type suma = 0;
            for(int k=0;k<3;k++)
                suma += m_macierz[i][k] * obiekt.m_macierz[k][j];
            wynik.m_macierz[i][j] = suma;
        }
    return wynik;
}

//przeciazenie operatora *=
template <class Type>
void Macierze_3x3<Type>::operator*=(const Macierze_3x3<Type> &obiekt)
{
    if(POKAZ_KOMUNIKATY_MACIERZE == true)
        cout<<"Uruchomiono metode mnozaca macierze (przeciazenie operatora: *=).\n";
    Type wynik[3][3];
    int i,j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            Type suma = 0;
            for(int k=0;k<3;k++)
                suma += m_macierz[i][k] * obiekt.m_macierz[k][j];
            wynik[i][j] = suma;
        }
    memcpy(m_macierz,wynik,9*sizeof(Type));
}

//liczenie wyznacznika
template <class Type>
double Macierze_3x3<Type>::oblicz_wyznacznik(void)
{
    if(POKAZ_KOMUNIKATY_MACIERZE == true)
        cout<<"Uruchomiono metode obliczajaca wyznacznik macierzy.\n";
    double wyznacznik =
    m_macierz[0][0] * m_macierz[1][1] * m_macierz[2][2] + m_macierz[0][1] * m_macierz[1][2] * m_macierz[2][0] +
    m_macierz[0][2] * m_macierz[1][0] * m_macierz[2][1] - m_macierz[2][0] * m_macierz[1][1] * m_macierz[0][2] -
    m_macierz[2][1] * m_macierz[1][2] * m_macierz[0][0] - m_macierz[2][2] * m_macierz[1][0] * m_macierz[0][1];
    return wyznacznik;
}

//przeciazenie operatora ==
template<class Type>
bool Macierze_3x3<Type>::operator==(const Macierze_3x3<Type> &obiekt)const
{
	if(POKAZ_KOMUNIKATY_MACIERZE == true)
		cout<<"Uruchomiono metode porownywania macierzy (przeciazenie operatora: ==).\n";
	bool wynik = true;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			if(m_macierz[i][j] != obiekt.m_macierz[i][j])
			{
				wynik = false;
				break;
			}
		if(wynik == false)
			break;
	}
	return wynik;
}
				
//drukowanie zawartosci
template <class Type>
ostream & operator<< (ostream &wyjscie,const Macierze_3x3<Type> &obiekt)
{
    if(POKAZ_KOMUNIKATY_MACIERZE == true)
        cout<<"Uruchomiono metode drukujaca zawartosc macierzy.\n";
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            wyjscie<<obiekt.m_macierz[i][j]<<"\t";
        wyjscie<<"\n";
    }
    return wyjscie;
}

#endif
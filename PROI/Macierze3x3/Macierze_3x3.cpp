//PROJEKT PIERWSZY: KLASY REPREZENTUJACE MACIERZE 3X3
//PRZYGOTOWAL: TOMASZ BOCHENSKI

#include "Macierze_3x3.h"

extern bool pokaz_komunikaty;

//konstruktor
Macierze_3x3::Macierze_3x3(double tablica[3][3])
{
    if(pokaz_komunikaty == true)
        cout<<"Uruchomiono konstruktor z parametrem.\n";
    memcpy(m_macierz,tablica,9*sizeof(double));
}

//konstruktor domyslny
Macierze_3x3::Macierze_3x3()
{
    if(pokaz_komunikaty == true)
        cout<<"Uruchomiono konstruktor domyslny.\n";
    memset(m_macierz,0,9*sizeof(double));
}

//destruktor
Macierze_3x3::~Macierze_3x3()
{
    if(pokaz_komunikaty == true)
        cout<<"Uruchomiono destruktor.\n";
}

//przeciazenie operatora +
Macierze_3x3 Macierze_3x3::operator+(const Macierze_3x3 &obiekt)const
{
    if(pokaz_komunikaty == true)
        cout<<"Uruchomiono metode dodajaca macierze (przeciazenie operatora: +).\n";
    Macierze_3x3 wynik;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            wynik.m_macierz[i][j] = m_macierz[i][j] + obiekt.m_macierz[i][j];
    return wynik;
}

//przeciazenie operatora +=
void Macierze_3x3::operator+=(const Macierze_3x3 &obiekt)
{
    if(pokaz_komunikaty == true)
        cout<<"Uruchomiono metode dodajaca macierze (przeciazenie operatora: +=).\n";
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            m_macierz[i][j] += obiekt.m_macierz[i][j];
}

//przeciazenie operatora -
Macierze_3x3 Macierze_3x3::operator-(const Macierze_3x3 &obiekt)const
{
    if(pokaz_komunikaty == true)
        cout<<"Uruchomiono metode odejmujaca macierze (przeciazenie operatora: -).\n";
    Macierze_3x3 wynik;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            wynik.m_macierz[i][j] = m_macierz[i][j] - obiekt.m_macierz[i][j];
    return wynik;
}

//przeciazenie operatora -=
void Macierze_3x3::operator-=(const Macierze_3x3 &obiekt)
{
    if(pokaz_komunikaty == true)
        cout<<"Uruchomiono metode odejmujaca macierze (przeciazenie operatora: -=).\n";
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            m_macierz[i][j] -= obiekt.m_macierz[i][j];
}

//przeciazenie operatora *
Macierze_3x3 Macierze_3x3::operator*(const Macierze_3x3 &obiekt)const
{
    if(pokaz_komunikaty == true)
        cout<<"Uruchomiono metode mnozaca macierze (przeciazenie operatora: *).\n";
    Macierze_3x3 wynik;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            double suma = 0;
            for(int k=0;k<3;k++)
                suma += m_macierz[i][k] * obiekt.m_macierz[k][j];
            wynik.m_macierz[i][j] = suma;
        }
    return wynik;
}

//przeciazenie operatora *=
void Macierze_3x3::operator*=(const Macierze_3x3 &obiekt)
{
    if(pokaz_komunikaty == true)
        cout<<"Uruchomiono metode mnozaca macierze (przeciazenie operatora: *=).\n";
    double wynik[3][3];
    int i,j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            double suma = 0;
            for(int k=0;k<3;k++)
                suma += m_macierz[i][k] * obiekt.m_macierz[k][j];
            wynik[i][j] = suma;
        }
    memcpy(m_macierz,wynik,9*sizeof(double));
}

//liczenie wyznacznika
double Macierze_3x3::oblicz_wyznacznik(void)
{
    if(pokaz_komunikaty == true)
        cout<<"Uruchomiono metode obliczajaca wyznacznik macierzy.\n";
    double wyznacznik =
    m_macierz[0][0] * m_macierz[1][1] * m_macierz[2][2] + m_macierz[0][1] * m_macierz[1][2] * m_macierz[2][0] +
    m_macierz[0][2] * m_macierz[1][0] * m_macierz[2][1] - m_macierz[2][0] * m_macierz[1][1] * m_macierz[0][2] -
    m_macierz[2][1] * m_macierz[1][2] * m_macierz[0][0] - m_macierz[2][2] * m_macierz[1][0] * m_macierz[0][1];
    return wyznacznik;
}

//drukowanie zawartosci
ostream & operator<<(ostream &wyjscie,const Macierze_3x3 &obiekt)
{
    if(pokaz_komunikaty == true)
        cout<<"Uruchomiono metode drukujaca zawartosc macierzy.\n";
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            wyjscie<<obiekt.m_macierz[i][j]<<"\t";
        wyjscie<<"\n";
    }
    return wyjscie;
}

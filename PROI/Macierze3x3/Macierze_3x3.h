//PROJEKT PIERWSZY: KLASY REPREZENTUJACE MACIERZE 3X3
//PRZYGOTOWAL: TOMASZ BOCHENSKI

#ifndef MACIERZE_3X3_H
#define MACIERZE_3X3_H
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class Macierze_3x3
{
    private:
        double m_macierz[3][3];
    public:
        Macierze_3x3(double tablica[3][3]);
        Macierze_3x3();
        ~Macierze_3x3();
        Macierze_3x3 operator+(const Macierze_3x3 &obiekt)const;
        void operator+=(const Macierze_3x3 &obiekt);
        Macierze_3x3 operator-(const Macierze_3x3 &obiekt)const;
        void operator-=(const Macierze_3x3 &obiekt);
        Macierze_3x3 operator*(const Macierze_3x3 &obiekt)const;
        void operator*=(const Macierze_3x3 &obiekt);
        double oblicz_wyznacznik(void);
        friend ostream & operator<<(ostream &wyjscie,const Macierze_3x3 &obiekt);
};

#endif // MACIERZE_3X3_H

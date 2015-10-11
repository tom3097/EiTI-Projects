//PROJEKT PIERWSZY: KLASY REPREZENTUJACE MACIERZE 3X3
//PRZYGOTOWAL: TOMASZ BOCHENSKI

#include <iostream>
#include "Macierze_3x3.h"

void ustaw_macierz(Macierze_3x3 &obiekt);
void instrukcja(void);

//deklaracja zmiennej decydujacej o tym, czy opcjonalne komunikaty beda wyswietlane
bool pokaz_komunikaty = true;

int main()
{
    //deklaracje trzech macierzy: na pierwszych dwoch dokonywane sa obliczenia, trzecia jest na wynik
    Macierze_3x3 macierz_1, macierz_2, macierz_3;
    double wyznacznik;

    instrukcja();

    while(true)
    {
        cout<<"Aby ponownie wyswietlic instrukcje wcisnij: 0.\n";
        //wczytywanie liczby decydujacej o tym, jakie dzialanie zostanie podjete
        int opcja;
        cin>>opcja;
        while(cin.fail() || opcja > 12 || opcja < 0)
        {
            //w razie blednego wprowadzenia czyszczenie bufora i ponowne wczytanie
            cin.clear();
            cin.sync();
            cout<<"Wprowadzono bledne dane. Prosze wprowadzic je ponownie.\n";
            cin>>opcja;
        }

        switch(opcja)
        {
            //0: wyswietlana zostaje instrukcja
            case 0:instrukcja(); break;
            //1: uzytkownik ma mozliwosc uzupelnienia pierwszej macierzy
            //w razie podania blednych danych uruchamiany jest konstruktor domyslny i macierz uzupelniana jest samymi zerami
            case 1: cout<<"Prosze wprowadzic liczby:\n";
            ustaw_macierz(macierz_1); break;
            //1: uzytkownik ma mozliwosc uzupelnienia drugiej macierzy
            //w razie podania blednych danych uruchamiany jest konstruktor domyslny i macierz uzupelniana jest samymi zerami
            case 2: cout<<"Prosze wprowadzic liczby:\n";
            ustaw_macierz(macierz_2); break;
            //3: wypisuje aktualnie ustawione macierze: pierwsza i druga
            case 3: cout<<"Macierz nr 1:\n"<<macierz_1<<endl;
            cout<<"Macierz nr 2:\n"<<macierz_2<<endl; break;
            //4: przeprowadzone zostaje dodawanie macierzy, nastepnie wyswietlona jest macierz wynikowa
            case 4: macierz_3 = macierz_1 + macierz_2;
            cout<<"Macierz wynikowa to:\n"<<macierz_3<<endl; break;
            //5: przeprowadzone zostaje dodawanie macierzy, wynik zostaje przypisany macierzy pierwszej
            case 5: macierz_1 += macierz_2;
            cout<<"Teraz macierz nr 1 to:\n"<<macierz_1<<endl; break;
            //6: przeprowadzone zostaje odejmowanie macierzy, nastepnie wyswietlona jest macierz wynikowa
            case 6: macierz_3 = macierz_1 - macierz_2;
            cout<<"Macierz wynikowa to:\n"<<macierz_3<<endl; break;
            //7: przeprowadzone zostaje odejmowanie macierzy, wynik zostaje przypisany macierzy pierwszej
            case 7: macierz_1 -= macierz_2;
            cout<<"Teraz macierz nr 1 to:\n"<<macierz_1<<endl; break;
            //8: przeprowadzone zostaje mnozenie macierzy, nastepnie wyswietlona jest macierz wynikowa
            case 8: macierz_3 = macierz_1 * macierz_2;
            cout<<"Macierz wynikowa to:\n"<<macierz_3<<endl; break;
            //9: przeprowadzone zostaje mnozenie macierzy, wynik zostaje przypisany macierzy pierwszej
            case 9: macierz_1 *=macierz_2;
            cout<<"Teraz macierz nr 1 to:\n"<<macierz_1<<endl; break;
            //10: obliczony zostaje wyznacznik macierzy
            case 10: wyznacznik = macierz_1.oblicz_wyznacznik();
            cout<<"Wyznacznik pierwszej macierzy wynosi: "<<wyznacznik<<endl; break;
            //11: zmiana opcji wyswietlania opcjonalnych komunikatow
            case 11: pokaz_komunikaty = !pokaz_komunikaty;
            cout<<"Ustawienia zostaly zmienione.\n"; break;
            //case 12: konczy dzialanie programu
            case 12: return 0;
        }
    }
}
void ustaw_macierz(Macierze_3x3 &obiekt)
{
    double tmp_macierz_3x3[3][3];
    //zmienna informujaca o poprawnosci wczytania danych
    bool prawidlowe_wczytywanie = true;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cin>>tmp_macierz_3x3[i][j];
            if(cin.fail())
            {
                cin.clear();
                cin.sync();
                //w przypadku wczytania blednych danych zmienna poprawne_wczytywanie zmieniana jest na false
                prawidlowe_wczytywanie = false;
                break;
            }
        }
        if(prawidlowe_wczytywanie == false)
            break;
    }
    //jesli wczytywanie odbylo sie prawidlowo, z wczytanych liczb mozna utworzyc macierz
    if(prawidlowe_wczytywanie == true)
        obiekt = Macierze_3x3(tmp_macierz_3x3);
    //jesli podczas wczytywania nastapily bledy, macierz tworzona jest przez konstruktor domyslny
    if(prawidlowe_wczytywanie == false)
        obiekt = Macierze_3x3();
}
void instrukcja(void)
{
    string info;
    if(pokaz_komunikaty == true)
        info = "WLACZONE";
    else
        info = "WYLACZONE";
    cout<<"     __________________________________________________________\n";
    cout<<"1) Ustaw pierwsza macierz\t\t2) Ustaw druga macierz\n";
    cout<<"3) Wyswietl macierze\t\t\t4) Dodawanie macierzy(+)\n";
    cout<<"5) Dodawanie macierzy(+=)\t\t6) Odejmowanie macierzy(-)\n";
    cout<<"7) Odejmowanie macierzy(-=)\t\t8) Mnozenie macierzy(*)\n";
    cout<<"9) Mnozenie macierzy(*=)\t\t10) Oblicz wyznacznik (macierz 1)\n";
    cout<<"11) Zmien ustawienia opcjonalnych komunikatow (aktualnie: "<<info<<")"<<endl;
    cout<<"12) Zakoncz dzialanie programu\n";
    cout<<"     __________________________________________________________\n";
}

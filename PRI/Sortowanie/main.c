//Sortowanie listy osob wedlug malejacego wieku
//Ostatnie poprawki: 01.12.2013
//przygotowal: Tomasz Bochenski

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define AKTUALNY_ROK 2013
#define LICZBA_MIESIECY 12
#define MAX_DL_NAZWY 40
#define MAX_DANYCH 40


typedef
struct {
unsigned int rok, mies, dzien;
} data;

typedef
struct {
int w_1,w_2;
} dlugosc_wyrazenia;

typedef
struct {
char nazwisko[MAX_DL_NAZWY];
char imie [MAX_DL_NAZWY];
data data_ur;
dlugosc_wyrazenia dlugosc;
} osoba;

    osoba lista[MAX_DANYCH];

int poprawnosc_daty(unsigned rok, unsigned miesiac, unsigned dzien);
void sortowanie_przez_wybieranie(unsigned rozmiar);
int main()
{
    printf("Wprowadzaj kolejne nazwiska, imiona i daty urodzenia w postaci:\n");
    printf("Nazwisko Imie rrrr-mm-dd\n");
    printf("Dane wprowadzone inaczej nie beda brane pod uwage.\n");
    printf("Nazwisko i imie nie moze miec powyzej 40 znakow.\n");

    char c;
    int i;
    int index =0;
    int liczba_osob;

    while(index<MAX_DANYCH)
    {
        poczatek:
        i=0;
        c=getchar();
        if(c!='\n')
        {
            while(isalpha(c) && i<MAX_DL_NAZWY)
            {
                lista[index].nazwisko[i]=c;
                i++;
                c=getchar();
            }
            lista[index].dlugosc.w_1=i;
            if(!isspace(c))
            {
                printf("Wpisane dane sa bledne. Prosze wpisac je powtornie.\n");
                while(getchar()!='\n');
                goto poczatek;
            }
            else if(c=='\n')
            {
                printf("Wpisane dane sa bledne. Prosze wpisac je powtornie.\n");
                goto poczatek;
            }
            else if(isspace(c))
            {
                i=0;
                c=getchar();
                while(isalpha(c) && i<MAX_DL_NAZWY)
                {
                    lista[index].imie[i]=c;
                    i++;
                    c=getchar();
                }
                lista[index].dlugosc.w_2=i;
                if(!isspace(c))
                {
                    printf("Wpisane dane sa bledne. Prosze wpisac je powtornie.\n");
                    while(getchar()!='\n');
                    goto poczatek;
                }
                else if(c=='\n')
                {
                    printf("Wpisane dane sa bledne. Prosze wpisac je powtornie.\n");
                    goto poczatek;
                }
                else if(isspace(c))
                {
                    c=getchar();
                    if(isspace(c))
                    {
                        printf("Wpisane dane sa bledne. Prosze wpisac je powtornie.\n");
                        while(getchar()!='\n');
                        goto poczatek;
                    }
                    else
                    {
                        ungetc(c, stdin);
                        if(scanf("%d-%d-%d",&lista[index].data_ur.rok,&lista[index].data_ur.mies,&lista[index].data_ur.dzien)!=3)
                        {
                            printf("Wpisane dane sa bledne. Prosze wpisac je powtornie.\n");
                            while(getchar()!='\n');
                            goto poczatek;
                        }
                        else if(getchar()!='\n')
                        {
                            printf("Wpisane dane sa bledne. Prosze wpisac je powtornie.\n");
                            while(getchar()!='\n');
                            goto poczatek;
                        }
                        else if(poprawnosc_daty(lista[index].data_ur.rok,lista[index].data_ur.mies,lista[index].data_ur.dzien)==0)
                        {
                            printf("Wpisana data jest niepoprawna.\n");
                            goto poczatek;
                        }
                    }
                }
            }
        index++;
        }
        else
            break;
    }

    liczba_osob=index;

    printf("Lista osob wraz z ich danymi:\n");
    for(index=0; index<liczba_osob; index++)
    {
        for(i=0;i<lista[index].dlugosc.w_1; i++)
            putchar(lista[index].nazwisko[i]);
        putchar(' ');
        for(i=0;i<lista[index].dlugosc.w_2;i++)
            putchar(lista[index].imie[i]);
        putchar(' ');
        printf("%04d-%02d-%02d\n", lista[index].data_ur.rok,lista[index].data_ur.mies, lista[index].data_ur.dzien);
    }

    sortowanie_przez_wybieranie(liczba_osob);
    putchar('\n');

    printf("Posortowana lista osob:\n");
    for(index=0; index<liczba_osob; index++)
    {
        for(i=0;i<lista[index].dlugosc.w_1; i++)
            putchar(lista[index].nazwisko[i]);
        putchar(' ');
        for(i=0;i<lista[index].dlugosc.w_2;i++)
            putchar(lista[index].imie[i]);
        putchar(' ');
        printf("%04d-%02d-%02d\n", lista[index].data_ur.rok,lista[index].data_ur.mies, lista[index].data_ur.dzien);
    }
    return 0;
}

int poprawnosc_daty(unsigned rok, unsigned miesiac, unsigned dzien)
{
    int max_dni;
    if(miesiac==4 || miesiac==6 || miesiac==9 || miesiac==11)
        max_dni=30;
    else if(miesiac==2)
        {
        if((rok%4==0 && rok%100!=0) || rok%400==0)
            max_dni=29;
        else
            max_dni=28;
        }
    else
        max_dni=31;
    if(rok>AKTUALNY_ROK || miesiac>LICZBA_MIESIECY || dzien>max_dni)
        return 0;
    else
        return 1;
}

void sortowanie_przez_wybieranie(unsigned rozmiar)
{
    int wsk;
    int i;
    int j;
    osoba pomocnicza;
    for (i = 0 ; i<(rozmiar - 1) ; i++ )
    {
        wsk = i;

        for ( j = i + 1 ; j<rozmiar ; j++ )
        {
            if (lista[wsk].data_ur.rok > lista[j].data_ur.rok )
                wsk = j;
            if (lista[wsk].data_ur.rok == lista[j].data_ur.rok)
            {
                if(lista[wsk].data_ur.mies > lista[j].data_ur.mies)
                    wsk = j;
                if(lista[wsk].data_ur.mies == lista[j].data_ur.mies)
                    if(lista[wsk].data_ur.dzien > lista[j].data_ur.dzien)
                        wsk = j;
            }
        }
        if ( wsk != i )
        {
            pomocnicza = lista[i];
            lista[i] = lista[wsk];
            lista[wsk] = pomocnicza;
        }
   }
}

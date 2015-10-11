//Przygotowal: Tomasz Bochenski, I3
//cwiczenie dodatkowe
//ostatnie poprawki: 30.01.2014

//program wczytuje kolory b-bialy, c-czarny do tablicy kwadratowej, nastepnie zgodnie z trescia zadania tworzy drzewo i wypisuje
//jego zawartosc metoda pre-order, gdzie b- bialy, c-czarny, s-szary(czyli czarny i bialy)
#include <stdio.h>
#include <stdlib.h>

struct drzewo
{
    int kolor;
    struct drzewo *nast1, *nast2, *nast3, *nast4;
};
struct drzewo *korzen = NULL;

void uzupelnij_tablice(int wymiar,char tablica[wymiar][wymiar]);
void stworz_drzewo(int wymiar, char tablica[wymiar][wymiar],int dlugosc);
void stworz_fragment(struct drzewo *wezel, int wymiar, char tablica[wymiar][wymiar],int dlugosc);
char czy_taka_sama(int wymiar,char tablica[wymiar][wymiar], int dlugosc);
void wypisz_pre (struct drzewo *wezel);

int main()
{
    int wymiar;
    printf("Prosze podac wymiar tablicy kwadratowej.\n");
    while(scanf("%d",&wymiar)!=1)
    {
        printf("Blad. Prosze wpisac ponownie.\n");
        while(getchar()!='\n');
    }
    while(getchar()!='\n');
    char tab[wymiar][wymiar];

    printf("Prosze podac %d elementow ciagu, ktorymi sa kolory.\n",wymiar*wymiar);
    printf("Do wyboru sa jedynie kolory czarny (wpisac: c) i bialy (wpisac: b)\n");
    printf("Pomocniczo zostana wyswietlone *.Informuja do ktorego momentu nalezy uzupelniac ciag.\n");
    int i;
    for(i=0; i<wymiar*wymiar; i++)
        printf("*");
    printf("\n");
    uzupelnij_tablice(wymiar,tab);

    stworz_drzewo(wymiar,tab,wymiar);
    printf("Wypisanie liter metoda pre-order:\n");
    wypisz_pre(korzen);
    return 0;
}

void stworz_fragment(struct drzewo *wezel, int wymiar, char tablica[wymiar][wymiar],int dlugosc)
{
    wezel->kolor = 's';
    char kolorek = czy_taka_sama(wymiar,tablica,dlugosc);
    if(kolorek=='c' || kolorek=='b')
    {
        wezel->kolor =kolorek;
        return;
    }
    wezel->nast1 = (struct drzewo*)malloc(sizeof(struct drzewo));
    wezel->nast2 = (struct drzewo*)malloc(sizeof(struct drzewo));
    wezel->nast3 = (struct drzewo*)malloc(sizeof(struct drzewo));
    wezel->nast4 = (struct drzewo*)malloc(sizeof(struct drzewo));

    stworz_fragment(wezel->nast1,wymiar,&tablica[0][0],dlugosc>>1);
    stworz_fragment(wezel->nast2,wymiar,&tablica[0][dlugosc>>1],dlugosc>>1);
    stworz_fragment(wezel->nast3,wymiar,&tablica[dlugosc>>1][0],dlugosc>>1);
    stworz_fragment(wezel->nast4,wymiar,&tablica[dlugosc>>1][dlugosc>>1],dlugosc>>1);
}
char czy_taka_sama(int wymiar,char tablica[wymiar][wymiar], int dlugosc)
{
    char wsk;
    int i,j;
    char kolor;
    kolor = tablica[0][0];
    if(kolor!='c' && kolor!= 'b')
    {
        printf("Wpisano niedozwolone kolory.Dozwolone kolory to: c,b.\n");
        exit(0);
    }
    for(i=0; i<dlugosc; i++)
        for(j=0; j<dlugosc; j++)
            if(tablica[i][j]!=kolor)
                return 's';
    return kolor;
}
void stworz_drzewo(int wymiar, char tablica[wymiar][wymiar],int dlugosc)
{
    korzen = (struct drzewo*)malloc(sizeof(struct drzewo));
    stworz_fragment(korzen,wymiar,tablica,dlugosc);
}
void wypisz_pre (struct drzewo *wezel)
{
    printf("[");
    if(wezel->kolor == 's')
    {
        printf("%c",wezel->kolor);
        wypisz_pre(wezel->nast1);
        wypisz_pre(wezel->nast2);
        wypisz_pre(wezel->nast3);
        wypisz_pre(wezel->nast4);
    }
    else
        printf("%c",wezel->kolor);
    printf("]");
}
void uzupelnij_tablice(int wymiar,char tablica[wymiar][wymiar])
{
    int i,j;
    for(i=0; i<wymiar; i++)
        for(j=0; j<wymiar; j++)
            scanf("%c",&tablica[i][j]);
}

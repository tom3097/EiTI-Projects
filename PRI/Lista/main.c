//Zadanie laboratoryjne numer 3/4
//Przygotowal: Tomasz Bocheñski
//Ostatnie poprawki: 18.01.2014


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SLOWO 20
#define POPRAWNE 1
#define NIEPOPRAWNE 0
#define POPRAWNE_KONIEC 2
#define NIEPOPRAWNE_KONIEC 3

struct element
{
    char slowo[MAX_SLOWO];
    struct element * nast;
    struct liczby * pierw_licz;
};

struct liczby
{
    int liczba;
    struct liczby * nast_liczba;
};

struct poprawnosc_danych
{
    int poprawnosc;
    struct liczby * adres_pierwszej;
};

struct element * pierwszy = NULL;

struct poprawnosc_danych * dodaj_liczby_z_klawiatury(void);
void usun_liczby(struct liczby * pierwsza_liczba);
void usun_pierwsze_slowo(void);
void usun_slowo_za(struct element *za);
struct element * znajdz_adres_przed(int n);
void dodaj_elementy_z_klawiatury(void);
void wyswietl_liste(void);
void instrukcja(void);
int wybor(void);
void usun_element(void);
void usun_wszystkie_elementy(void);
void komunikaty(int nr_kom);
struct poprawnosc_danych * dodaj_liczby_z_pliku(FILE *lokalizacja);
void dodaj_elementy_z_pliku(FILE *lokalizacja);
void wczytaj_z_pliku(void);
void zapisz_do_pliku(void);
int czy_istnieje(char *nazwa_pliku);
int czy_zapisywac(int wsk);
void autowczytywanie(void);
void autozapisywanie(void);


int main()
{
    int stan;
    instrukcja();
    stan = wybor();

    autowczytywanie();
    while(1)
    {
        switch(stan)
        {
            case 1: wyswietl_liste();
            komunikaty(18);
            break;
            case 2: dodaj_elementy_z_klawiatury();
            komunikaty(18);
            break;
            case 3: wczytaj_z_pliku();
            komunikaty(18);
            break;
            case 4: usun_element();
            komunikaty(18);
            break;
            case 5: usun_wszystkie_elementy();
            komunikaty(18);
            break;
            case 6: zapisz_do_pliku();
            komunikaty(18);
            break;
            case 7: autozapisywanie();
            exit(0);

        }
        stan = wybor();
    }
    return 0;
}
struct poprawnosc_danych * dodaj_liczby_z_klawiatury(void)
{
    struct liczby * head = NULL;
    struct liczby * aktualny, *poprzedni, *tmp;
    struct poprawnosc_danych * pop;
    int n;
    int stan;

    stan = scanf("%d",&n);
    while(stan==1)  //wczytuje liczby, jednoczesnie je sortuje
    {
        if(n==0)
            break;
        aktualny = (struct liczby *)malloc(sizeof(struct liczby));
        aktualny->liczba = n;
        if(head==NULL)
        {
            aktualny->nast_liczba = NULL;
            head = aktualny;
        }
        else
        {
            if(n < head->liczba)
            {
                aktualny->nast_liczba = head;
                head = aktualny;
            }
            else
            {
                tmp = head;
                while(tmp!= NULL)
                {
                    if(n >= tmp->liczba)
                    {
                        poprzedni = tmp;
                        tmp = tmp->nast_liczba;
                    }
                    else
                        break;
                }
                poprzedni->nast_liczba = aktualny;
                aktualny->nast_liczba = tmp;
            }
        }
        stan = scanf("%d", &n);
    }
    while(getchar()!='\n');
    pop = (struct poprawnosc_danych*)malloc(sizeof(struct poprawnosc_danych));
    if(stan == 0)   //przekazuje informacje czy wczytywaie odbylo sie prawidlowo czy nie
    {
        komunikaty(0);
        pop->poprawnosc = NIEPOPRAWNE;
        usun_liczby(head);
    }
    if(stan == 1)
    {
        pop->poprawnosc = POPRAWNE;
        pop->adres_pierwszej = head;
    }

    return pop;
}
void usun_liczby(struct liczby * pierwsza_liczba)   // usuwa liste liczb
{
    struct liczby *p, *q;
    p=pierwsza_liczba;
    while(p!=NULL)
    {
        q = p->nast_liczba;
        free(p);
        p=q;
    }
}
void usun_pierwsze_slowo(void)  // usuwa wskaznik na pierwsze slowo
{
    struct element *tmp;
    tmp = pierwszy;
    pierwszy= tmp->nast;
    free(tmp);
}
void usun_slowo_za(struct element *za)  // usuwa wskaznik na slowo za elementem "za"
{
    struct element * tmp;
    tmp = za->nast;
    za->nast = tmp->nast;
    free(tmp);
}
void dodaj_elementy_z_klawiatury(void)      // funkcja dodaje elementy do glownej listy
{
    struct element *poprzedni, * aktualny;
    struct poprawnosc_danych * stan;
    char tmp[MAX_SLOWO];
    char ch;
    komunikaty(1);
    ch = getchar();
    while(ch != '\n')   // po przekazaniu pustej lini koncze wczytywanie
    {
        ungetc(ch,stdin);

        scanf("%20s", tmp);
        aktualny = (struct element *)malloc(sizeof(struct element));
        aktualny->nast = NULL;
        strcpy(aktualny->slowo, tmp);

        if (pierwszy == NULL)
            pierwszy = aktualny;
        else
        {
            poprzedni = pierwszy;
            while(poprzedni->nast != NULL)
                poprzedni = poprzedni->nast;
            poprzedni->nast = aktualny;
        }
        stan = dodaj_liczby_z_klawiatury(); // wywoluje funkcje dodajaca liczby
        if(stan->poprawnosc == NIEPOPRAWNE)     // sprawdzam czy podczas dodawania liczb nie zostaly wpisane niedozwolone znaki
        {                                       // jesli tak to usuwam to slowo
            if(aktualny == pierwszy)
                usun_pierwsze_slowo();
            else
                usun_slowo_za(poprzedni);
        }
        else
        {
            aktualny->pierw_licz = stan->adres_pierwszej;
            poprzedni = aktualny;
        }
        free(stan);
        ch = getchar();
    }
    komunikaty(2);
}
void wyswietl_liste(void)   // wyswietla wszystkie slowa i liczby
{
    struct element * tmp_slowo;
    struct liczby * tmp_liczba;
    tmp_slowo=pierwszy;
    int numer = 1;
    if(tmp_slowo==NULL)
        komunikaty(3);
    else
        komunikaty(4);
        while(tmp_slowo!=NULL)
        {
            printf("%d:\t%s\t",numer,tmp_slowo->slowo);
            tmp_liczba=tmp_slowo->pierw_licz;
            while(tmp_liczba!= NULL)
            {
                printf("%d\t",tmp_liczba->liczba);
                tmp_liczba = tmp_liczba->nast_liczba;
            }
            tmp_slowo = tmp_slowo->nast;
            numer++;
            printf("\n");
        }
}
void instrukcja(void)
{
    printf("________________________________________________________________________________\n");
    printf("Wybierz cyfre odpowiadajaca dzialaniu ktore chcesz przeprowadzic.\n");
    printf("1) Wyswietl liste                           2) Dodaj elementy z klawiatury\n");
    printf("3) Dodaj elementy z pliku                   4) Usun pojedynczy element\n");
    printf("5) Usun wszystkie elementy                  6) Zapisz liste do pliku\n");
    printf("7) Zakoncz dzialanie programu\n");
    printf("________________________________________________________________________________\n");
}
int wybor(void) // wczytuje liczbe ktora okresli jakie dzialanie zostanie podjete przez program
{
    int wybor;
    while(scanf("%d",&wybor)!=1 || wybor<1 || wybor>7)
    {
        komunikaty(5);
        while(getchar()!='\n');
    }
    while(getchar()!='\n');
    return wybor;
}
struct element * znajdz_adres_przed(int n)  // znajduje adres elementu przed poszukiwanym elementem
{
    struct element *poprzedni = NULL;
    struct element *tmp;
    int i;
    for(i=1, tmp=pierwszy; i<n && tmp!= NULL; i++, tmp=tmp->nast)
        poprzedni = tmp;
    return poprzedni;
}
void usun_element(void) // usuwam element
{
    if(pierwszy == NULL)
    {
        komunikaty(6);
        return;
    }
    struct element *przed_usuwanym;
    int nr_wiersza;
    komunikaty(7);
    if(scanf("%d",&nr_wiersza)!= 1)
        komunikaty(8);
    else
    {
        if(nr_wiersza<1)
            komunikaty(8);
        else
        {
            przed_usuwanym = znajdz_adres_przed(nr_wiersza);
            if(przed_usuwanym == NULL)  // jesli adres jest rowny NULL znaczy ze musi usuwanym elementem musi byc "pierwszy"
            {
                usun_liczby(pierwszy->pierw_licz);
                usun_pierwsze_slowo();
                komunikaty(9);
            }
            else if(przed_usuwanym->nast == NULL)   //znaczy to ze element taki nie istnieje, nie ma co usuwac
                komunikaty(8);
            else
            {
                usun_liczby(przed_usuwanym->nast->pierw_licz);
                usun_slowo_za(przed_usuwanym);
                komunikaty(9);
            }
        }
    }
    while(getchar()!='\n');
}
void usun_wszystkie_elementy(void)
{
    struct element *to_kill, *tmp;

    to_kill = pierwszy;
    while(to_kill!=NULL)
    {
        tmp=to_kill->nast;
        usun_liczby(to_kill->pierw_licz);
        free(to_kill);
        to_kill=tmp;
    }
    pierwszy = NULL;
    komunikaty(19);
}
void komunikaty(int nr_kom)
{
    char *komunikat[] = {
        "\tNIEPOPRAWNE DANE\n",  //0
        "\tWCZYTYWANIE ROZPOCZETE\n",   //1
        "\tWCZYTYWANIE ZAKONCZONE\n",   //2
        "\tLISTA JEST PUSTA\n", //3
        "\tLISTA\n",    //4
        "\tPODAJ LICZBE 1-6 ZGODNIE Z INSTRUKCJA\n",    //5
        "\tLISTA JEST PUSTA. NIE MOZNA Z NIEJ NIC USUNAC\n",    //6
        "\tPODAJ WIERSZ KTORY CHCESZ SKASOWAC\n",   //7
        "\tTAKI WIERSZ NIE ISTNIEJE\n", //8
        "\tPODANY WIERSZ ZOSTAL USUNIETY\n",    //9
        "\tPODAJ NAZWE PLIKU (do 20 znakow, dluzsze beda skracane)\n",  //10
        "\tNIE UDALO SIE OTWORZYC PLIKU\n", //11
        "\tPOPRAWNE ELEMENTY ZOSTALY DODANE\n", //12
        "\tLISTA ZOSTALA ZAPISANA\n",   //13
        "\tLISTA NIE ZOSTALA ZAPISANA\n",    //14
        "\tPLIK O TEJ NAZWIE JUZ ISTNIEJE. CZY CHCESZ GO NADPISAC?\n",  //15
        "\t( jesli tak wcisnij 0, jesli nie wcisnij 1 )\n", //16
        "\tPROSZE WPISAC LICZBE ZGODNIE Z INSTRUKCJA\n",     //17
        "\tCo teraz chcesz zrobic?\n",   //18
        "\tUSUWANIE ZAKONCZONE\n",   //19
        "\tPODANY PLIK OTWIERANY MOZE BYC JEDYNIE AUTOMATYCZNIE\n"  //20
        };
    printf("%s", komunikat[nr_kom]);
}
struct poprawnosc_danych * dodaj_liczby_z_pliku(FILE *lokalizacja)
{
    struct liczby * head = NULL;
    struct liczby * aktualny, *poprzedni, *tmp;
    struct poprawnosc_danych * pop;
    int n, stan, kont;

    while((stan=fscanf(lokalizacja,"%d",&n))==1)
    {
        if(n==0)
            break;
        aktualny = (struct liczby *)malloc(sizeof(struct liczby));
        aktualny->liczba = n;

        if(head==NULL)
        {
            aktualny->nast_liczba = NULL;
            head = aktualny;
        }
        else
        {
            if(n < head->liczba)
            {
                aktualny->nast_liczba = head;
                head = aktualny;
            }
            else
            {
                tmp = head;
                while(tmp!= NULL)
                {
                    if(n >= tmp->liczba)
                    {
                        poprzedni = tmp;
                        tmp = tmp->nast_liczba;
                    }
                    else
                        break;
                }
                poprzedni->nast_liczba = aktualny;
                aktualny->nast_liczba = tmp;
            }
        }
    }
    if(stan != EOF)
        while((kont=fgetc(lokalizacja))!='\n' && kont!=EOF);
    pop = (struct poprawnosc_danych*)malloc(sizeof(struct poprawnosc_danych));

    if(stan != 1)
    {
        if(stan==0)
            pop->poprawnosc = NIEPOPRAWNE;
        if(stan==EOF)
            pop->poprawnosc = NIEPOPRAWNE_KONIEC;
        usun_liczby(head);
    }
    if(stan == 1)
    {
        if(kont!=EOF)
            pop->poprawnosc = POPRAWNE;
        if(kont==EOF)
            pop->poprawnosc = POPRAWNE_KONIEC;
        pop->adres_pierwszej = head;
    }
    return pop;
}
void dodaj_elementy_z_pliku(FILE *lokalizacja)
{
    struct element *poprzedni, * aktualny;
    struct poprawnosc_danych * stan;
    char tmp[MAX_SLOWO];

    while(fscanf(lokalizacja,"%20s",tmp)!=EOF)
    {
        aktualny = (struct element *)malloc(sizeof(struct element));
        aktualny->nast = NULL;
        strcpy(aktualny->slowo, tmp);

        if (pierwszy == NULL)
            pierwszy = aktualny;
        else
        {
            poprzedni = pierwszy;
            while(poprzedni->nast != NULL)
                poprzedni = poprzedni->nast;
            poprzedni->nast = aktualny;
        }
        stan = dodaj_liczby_z_pliku(lokalizacja);
        if(stan->poprawnosc == NIEPOPRAWNE)
        {
            if(aktualny == pierwszy)
                usun_pierwsze_slowo();
            else
                usun_slowo_za(poprzedni);
        }
        if(stan->poprawnosc == NIEPOPRAWNE_KONIEC)
        {
            if(aktualny == pierwszy)
                usun_pierwsze_slowo();
            else
                usun_slowo_za(poprzedni);
            break;
        }
        if(stan->poprawnosc == POPRAWNE)
        {
            aktualny->pierw_licz = stan->adres_pierwszej;
            poprzedni = aktualny;
        }
        if(stan->poprawnosc == POPRAWNE_KONIEC)
        {
            aktualny->pierw_licz = stan->adres_pierwszej;
            poprzedni = aktualny;
            break;
        }
        free(stan);
    }
}
void wczytaj_z_pliku(void)
{
    FILE *fp;
    char nazwa_pliku[24];
    komunikaty(10);

    scanf("%20s",nazwa_pliku);
    while(getchar()!='\n');

    strcat(nazwa_pliku,".txt");
    if(strcmp(nazwa_pliku,"auto_odczyt_zapis.txt")==0)
        komunikaty(20);
    else
    {
        fp = fopen(nazwa_pliku,"r");
        if(fp == NULL)
            komunikaty(11);
        else
        {
            dodaj_elementy_z_pliku(fp);
            fclose(fp);
            komunikaty(12);
        }
    }
}
void zapisz_do_pliku(void)
{
    struct element * tmp_slowo;
    struct liczby * tmp_liczba;
    FILE *fp;
    char *nazwa_pliku[24];
    int tmp, stan;
    komunikaty(10);

    scanf("%20s",nazwa_pliku);
    while(getchar()!='\n');

    strcat(nazwa_pliku,".txt");
    if(strcmp(nazwa_pliku,"auto_odczyt_zapis.txt")==0)
        komunikaty(20);
    else
    {
        tmp = czy_istnieje(nazwa_pliku);
        stan = czy_zapisywac(tmp);
        if(stan == 0)
        {
            fp = fopen(nazwa_pliku,"w");
            if(fp == NULL)
                komunikaty(11);
            else
            {
                tmp_slowo=pierwszy;
                while(tmp_slowo!=NULL)
                {
                    fprintf(fp,"%s\t",tmp_slowo->slowo);
                    tmp_liczba=tmp_slowo->pierw_licz;
                    while(tmp_liczba!= NULL)
                    {
                        fprintf(fp,"%d\t",tmp_liczba->liczba);
                        tmp_liczba = tmp_liczba->nast_liczba;
                    }
                    fprintf(fp,"0\t");
                    tmp_slowo = tmp_slowo->nast;
                    fprintf(fp,"\n");
                }
                fclose(fp);
            }
            komunikaty(13);
        }
        else
            komunikaty(14);
    }
}
int czy_istnieje(char *nazwa_pliku)
{
    FILE *fp;
    int wsk;
    fp = fopen(nazwa_pliku,"r");
    if(fp == NULL)
        wsk = 0;
    else
    {
        wsk = 1;
        fclose(fp);
    }
    return wsk;
}
int czy_zapisywac(int wsk)
{
    int stan;

    if(wsk == 1)
    {
        komunikaty(15);
        komunikaty(16);
        while(scanf("%d",&stan)!= 1 || stan<0 || stan>1)
        {
            komunikaty(17);
            while(getchar()!='\n');
        }
        while(getchar()!='\n');
    }
    else
        stan = 0;
    return stan;
}
void autowczytywanie(void)
{
    FILE *fp;
    fp=fopen("auto_odczyt_zapis.txt","r");
    if(fp != NULL)
    {
        dodaj_elementy_z_pliku(fp);
        fclose(fp);
    }
}
void autozapisywanie(void)
{
    FILE *fp;
    struct element *tmp_slowo;
    struct liczby *tmp_liczba;
    fp=fopen("auto_odczyt_zapis.txt","w");
    if(fp != NULL)
    {
        tmp_slowo=pierwszy;
        while(tmp_slowo!=NULL)
        {
            fprintf(fp,"%s\t",tmp_slowo->slowo);
            tmp_liczba=tmp_slowo->pierw_licz;
            while(tmp_liczba!= NULL)
            {
                fprintf(fp,"%d\t",tmp_liczba->liczba);
                tmp_liczba = tmp_liczba->nast_liczba;
            }
            fprintf(fp,"0\t");
            tmp_slowo = tmp_slowo->nast;
            fprintf(fp,"\n");
        }
        fclose(fp);
    }
}

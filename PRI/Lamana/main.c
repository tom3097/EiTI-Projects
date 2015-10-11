#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//program liczacy dlugosc lamanej
//Tomasz Bochenski
//ostatnie poprawki: 11 listopad
int main()
{
    double x1, y1, x2, y2;
    double d;
    double suma=0;
    int stan;
    printf("Program liczy dlugosc lamanej.\n");
    printf("Podanie wspolrzednych (0,0) konczy dalsze wczytywanie.\n");
    do
        {
        stan=scanf("%lf %lf",&x1,&y1);
        if (stan!=2)
            {
            printf("Dane ktore wlasnie wpisales sa nieprawidlowe i nie beda brane pod uwage.\n");
            printf("Wpisz nowe dane.\n");
            while(getchar()!='\n');
            }
        }
    while(stan!=2);


    if(x1!=0 || y1!=0)
        {
        do
            {
            do
                {
                stan=scanf("%lf %lf",&x2,&y2);
                if (stan!=2)
                    {
                    printf("Dane ktore wlasnie wpisales sa nieprawidlowe i nie beda brane pod uwage.\n");
                    printf("Wpisz nowe dane.\n");
                    while(getchar()!='\n');
                    }
                }
            while(stan!=2);
            if(x2==0 && y2==0)
                printf("Dlugosc lamanej wynosi %.3lf", suma);
            else
                {
                d=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
                suma+=d;
                x1=x2;
                y1=y2;
                }
            }
        while(x2!=0 || y2!=0);
        }
    else
        printf("Dlugosc lamanej wynosi %.3lf", suma);
    return 0;
}

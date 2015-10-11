/// Przygotowal: Tomasz Bochenski
/// Opis pliku: plik naglowkowy zawierajacy definicje stalych oraz struktur wykorzystywanych w dalszej czesci implementacji

#ifndef STRUKTURY_STALE_H
#define STRUKTURY_STALE_H

#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define SEMAFOR_KLUCZ ftok(".",1500)
#define PAMIEC_X_KLUCZ ftok(".",3500)
#define PAMIEC_Y_KLUCZ ftok(".",4500)
#define PAMIEC_Z_KLUCZ ftok(".",6500)

enum { ZAJETE_X, PUSTE_X, ZAJETE_Y, PUSTE_Y, ZAJETE_Z, PUSTE_Z, MUTEX_X, MUTEX_Y, MUTEX_Z, LICZNIK};

#define SEMAFORY_ILOSC 10
#define BUFOR_ROZMIAR 5
#define PRODUKCJA_TRWA 1

struct Bufor
{
	char elementy[BUFOR_ROZMIAR];
	unsigned int pierwszy_wolny;
	unsigned int pierwszy_zajety;
};

#endif // STRUKTURY_STALE_H

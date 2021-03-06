// Przygotowal: Tomasz Bochenski
// Opis pliku: plik wykonywalny z kodem 'robota typu Y', ktory zajmuje sie produkcja elementow typu Y oraz wkladaniem ich do bufora Y

#include "Struktury_Stale.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	struct sembuf semafor;
	struct Bufor *bufor_Y;
	int zarodek;
	int produktInt;
	char produktChar;
	int max_czas_Y;
	int czas_pracy;
	int semafor_id;
	int pamiec_id_Y;

	/// odczytuje maksymalny czas wykonywania oraz zarodek podany jako argument funkcji main
	if(argc != 3)
	{
		printf("Bledna liczba argumentow dla wywolania pliku 'robot typu Y'\n");
		return -1;
	}
	max_czas_Y = atoi(argv[1]);
	zarodek = atoi(argv[2]);


	/// pobieram id wczesniej utworzonych semaforow
	semafor_id = semget(SEMAFOR_KLUCZ, SEMAFORY_ILOSC, 0);
	if(semafor_id == -1)
	{
		printf("Blad przy probie uzyskania id semaforow\n");
		return -1;
	}

	/// pobieram id wczesniej utworzonego segmentu pamieci wspoldzielonej dla bufora Y
	pamiec_id_Y = shmget(PAMIEC_Y_KLUCZ, sizeof(struct Bufor), 0);
	if(pamiec_id_Y == -1)
	{
		printf("Blad przy probie uzyskania id pamieci Y\n");
		return -1;
	}

	srand(zarodek);

	//printf("Uruchomiono proces 'robot typu Y'.\n");
	printf("Robot_Y  %d : POCZATEK PRACY.\n", getpid());

	while(PRODUKCJA_TRWA)
	{
		/// sprawdzam czy zakonczyc produkcje
		if(semctl(semafor_id, LICZNIK, GETVAL, 0) == 0)
		{
			printf("Robot_Y  %d : KONIEC PRACY.\n", getpid());
			return 0;
		}	
		/// operacja P na semaforze PUSTE_Y
		semafor.sem_num = PUSTE_Y;
		semafor.sem_op = -1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacji na semaforze\n");
			return -1;
		}

		/// operaca P na semaforze MUTEX_Y
		semafor.sem_num = MUTEX_Y;
		semafor.sem_op = -1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacji na semaforze\n");
			return -1;
		}

		/// podlaczam segment pamieci wspoldzielonej do pamieci adresowej procesu
		if((bufor_Y = shmat(pamiec_id_Y, NULL, 0)) == (struct Bufor*)-1 )
		{
			printf("Blad przy podlaczaniu segmentu pamieci wspoldzielonej dla procesu 'robot typu Y'\n");
			return -1;
		}

		/// symuluje czas pracy
		czas_pracy = rand()%max_czas_Y + 1;
		sleep(czas_pracy);

		/// produkowanie elementu Y
		produktInt = 97 + rand()%10;
		produktChar = (char)produktInt;

		printf("*** Robot_Y  %d : Wyprodukowano element typu Y. ***\n", getpid());

		/// wkladanie produktu w odpowiednie miesce w buforze Y
		bufor_Y->elementy[bufor_Y->pierwszy_wolny] = produktChar;
		bufor_Y->pierwszy_wolny = (bufor_Y->pierwszy_wolny + 1) % BUFOR_ROZMIAR;

		/// odlaczam segment pamieci wspoldzielonej od pamieci adresowej procesu
		if(shmdt(bufor_Y) == -1)
		{
			printf("Blad przy probie odlaczenia segment pamieci wspoldzielonej dla procesu 'robot typu Y'\n");
			return -1;
		}

		/// operacja V na semaforze MUTEX_Y
		semafor.sem_num = MUTEX_Y;
		semafor.sem_op = 1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacji na semaforze\n");
			return -1;
		}

		/// operacja V na semaforze ZAJETE_Y
		semafor.sem_num = ZAJETE_Y;
		semafor.sem_op = 1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacji na semaforze\n");
			return -1;
		}
	}
	return 0;
}

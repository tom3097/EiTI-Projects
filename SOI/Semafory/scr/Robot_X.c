/// Przygotowal: Tomasz Bochenski
/// Opis pliku: plik wykonywalny z kodem 'robota typu X', ktory zajmuje sie produkcja elementow typu X oraz wkladaniem ich do bufora X

#include "Struktury_Stale.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	struct sembuf semafor;
	struct Bufor *bufor_X;
	int zarodek;
	int produktInt;
	char produktChar;
	int max_czas_X;
	int czas_pracy;
	int semafor_id;
	int pamiec_id_X;


	/// odczytuje maksymalny czas wykonywania oraz zarodek podany jako argument funkcji main
	if(argc != 3)
	{
		printf("Bledna liczba argumentow dla wywolania pliku 'robot typu X'\n");
		return -1;
	}
	max_czas_X = atoi(argv[1]);
	zarodek = atoi(argv[2]);


	/// pobieram id wczesniej utworzonych semaforow
	semafor_id = semget(SEMAFOR_KLUCZ, SEMAFORY_ILOSC, 0);
	if(semafor_id == -1)
	{
		printf("Blad przy probie uzyskania id semaforow\n");
		return -1;
	}

	/// pobieram id wczesniej utworzonego segmentu pamieci wspoldzielonej dla bufora X
	pamiec_id_X = shmget(PAMIEC_X_KLUCZ, sizeof(struct Bufor), 0);
	if(pamiec_id_X == -1)
	{
		printf("Blad przy probie uzyskania id pamieci X\n");
		return -1;
	}

	srand(zarodek);

	//printf("Uruchomiono proces 'robot typu X'.\n");
	printf("Robot_X  %d : POCZATEK PRACY.\n", getpid());

	while(PRODUKCJA_TRWA)
	{
		/// sprawdzam czy zakonczyc produkcje
		if(semctl(semafor_id, LICZNIK, GETVAL, 0) == 0)
		{
			printf("Robot_X  %d : KONIEC PRACY.\n", getpid());
			return 0;
		}	
		/// operacja P na semaforze PUSTE_X
		semafor.sem_num = PUSTE_X;
		semafor.sem_op = -1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacji na semaforze\n");
			return -1;
		}

		/// operaca P na semaforze MUTEX_X
		semafor.sem_num = MUTEX_X;
		semafor.sem_op = -1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacji na semaforze\n");
			return -1;
		}
		
		/// podlaczam segment pamieci wspoldzielonej do pamieci adresowej procesu
		if((bufor_X = shmat(pamiec_id_X, NULL, 0)) == (struct Bufor*)-1 )
		{
			printf("Blad przy podlaczaniu segmentu pamieci wspoldzielonej dla procesu 'robot typu X'\n");
			return -1;
		}
			
		/// symuluje czas pracy
		czas_pracy = rand()%max_czas_X + 1;
		sleep(czas_pracy);

		/// produkowanie elementu X
		produktInt = 48 + rand()%10;
		produktChar = (char)produktInt;

		printf("*** Robot_X  %d : Wyprodukowano element typu X. ***\n", getpid());

		/// wkladanie produktu w odpowiednie miesce w buforze X
		bufor_X->elementy[bufor_X->pierwszy_wolny] = produktChar;
		bufor_X->pierwszy_wolny = (bufor_X->pierwszy_wolny + 1) % BUFOR_ROZMIAR;

		/// odlaczam segment pamieci wspoldzielonej od pamieci adresowej procesu
		if(shmdt(bufor_X) == -1)
		{
			printf("Blad przy probie odlaczenia segment pamieci wspoldzielonej dla procesu 'robot typu X'\n");
			return -1;
		}

		/// operacja V na semaforze MUTEX_X
		semafor.sem_num = MUTEX_X;
		semafor.sem_op = 1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacji na semaforze\n");
			return -1;
		}

		/// operacja V na semaforze ZAJETE_X
		semafor.sem_num = ZAJETE_X;
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

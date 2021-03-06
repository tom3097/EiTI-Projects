/// Przygotowal: Tomasz Bochenski
/// Opis pliku: plik wykonywalny z kodem 'robota typu Z', ktory zajmuje sie produkcja elementow typu Z oraz wkladaniem ich do bufora Z

#include "Struktury_Stale.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	struct sembuf semafor;
	struct Bufor *bufor_Z;
	int zarodek;
	int produktInt;
	char produktChar;
	int max_czas_Z;
	int czas_pracy;
	int semafor_id;
	int pamiec_id_Z;

	/// odczytuje maksymalny czas wykonywania oraz zarodek podany jako argument funkcji main
	if(argc != 3)
	{
		printf("Bledna liczba argumentow dla wywolania pliku 'robot typu Z'\n");
		return -1;
	}
	max_czas_Z = atoi(argv[1]);
	zarodek = atoi(argv[2]);


	/// pobieram id wczesniej utworzonych semaforow
	semafor_id = semget(SEMAFOR_KLUCZ, SEMAFORY_ILOSC, 0);
	if(semafor_id == -1)
	{
		printf("Blad przy probie uzyskania id semaforow\n");
		return -1;
	}

	/// pobieram id wczesniej utworzonego segmentu pamieci wspoldzielonej dla bufora Z
	pamiec_id_Z = shmget(PAMIEC_Z_KLUCZ, sizeof(struct Bufor), 0);
	if(pamiec_id_Z == -1)
	{
		printf("Blad przy probie uzyskania id pamieci Z\n");
		return -1;
	}

	srand(zarodek);

	//printf("Uruchomiono proces 'robot typu Z'.\n");
	printf("Robot_Z  %d : POCZATEK PRACY.\n", getpid());

	while(PRODUKCJA_TRWA)
	{
		/// sprawdzam czy zakonczyc produkcje
		if(semctl(semafor_id, LICZNIK, GETVAL, 0) == 0)
		{
			printf("Robot_Z  %d : KONIEC PRACY.\n", getpid());
			return 0;
		}	
		/// operacja P na semaforze PUSTE_Z
		semafor.sem_num = PUSTE_Z;
		semafor.sem_op = -1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacji na semaforze\n");
			return -1;
		}

		/// operaca P na semaforze MUTEX_Z
		semafor.sem_num = MUTEX_Z;
		semafor.sem_op = -1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacji na semaforze\n");
			return -1;
		}

		/// podlaczam segment pamieci wspoldzielonej do pamieci adresowej procesu
		if((bufor_Z = shmat(pamiec_id_Z, NULL, 0)) == (struct Bufor*)-1 )
		{
			printf("Blad przy podlaczaniu segmentu pamieci wspoldzielonej dla procesu 'robot typu Z'\n");
			return -1;
		}

		/// symuluje czas pracy
		czas_pracy = rand()%max_czas_Z + 1;
		sleep(czas_pracy);

		/// produkowanie elementu Z
		produktInt = 48 + rand()%10;
		produktChar = (char)produktInt;

		printf("*** Robot_Z  %d : Wyprodukowano element typu Z.***\n", getpid());

		/// wkladanie produktu w odpowiednie miesce w buforze Z
		bufor_Z->elementy[bufor_Z->pierwszy_wolny] = produktChar;
		bufor_Z->pierwszy_wolny = (bufor_Z->pierwszy_wolny + 1) % BUFOR_ROZMIAR;

		/// odlaczam segment pamieci wspoldzielonej od pamieci adresowej procesu
		if(shmdt(bufor_Z) == -1)
		{
			printf("Blad przy probie odlaczenia segment pamieci wspoldzielonej dla procesu 'robot typu Z'\n");
			return -1;
		}

		/// operacja V na semaforze MUTEX_Z
		semafor.sem_num = MUTEX_Z;
		semafor.sem_op = 1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacji na semaforze\n");
			return -1;
		}

		/// operacja V na semaforze ZAJETE_Z
		semafor.sem_num = ZAJETE_Z;
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






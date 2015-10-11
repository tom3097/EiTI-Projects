/// Przygotowal: Tomasz Bochenski
/// Opis pliku: plik wykonywalny z kodem 'robota typu Creator', ktory zajmuje sie produkcja napisow z elementow typu X, Y, Z, oraz wyswietlaniem tych napisow

#include "Struktury_Stale.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	struct sembuf semafor;
	struct Bufor *bufor_X;
	struct Bufor *bufor_Y;
	struct Bufor *bufor_Z;
	char produkt_koncowy[4];
	int czas_pracy;
	int semafor_id;
	int pamiec_id_X;
	int pamiec_id_Y;
	int pamiec_id_Z;

	/// odczytuje czas wykonywania podany jako argument funkcji main
	if(argc != 2)
	{
		printf("Bledna liczba argumentow dla wywolania pliku 'robot typu CREATOR'\n");
		return -1;
	}
	czas_pracy = atoi(argv[1]);

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

	/// pobieram id wczesniej utworzonego segmentu pamieci wspoldzielonej dla bufora Y
	pamiec_id_Y = shmget(PAMIEC_Y_KLUCZ, sizeof(struct Bufor), 0);
	if(pamiec_id_Y == -1)
	{
		printf("Blad przy probie uzyskania id pamieci Y\n");
		return -1;
	}

	/// pobieram id wczesniej utworzonego segmentu pamieci wspoldzielonej dla bufora Z
	pamiec_id_Z = shmget(PAMIEC_Z_KLUCZ, sizeof(struct Bufor), 0);
	if(pamiec_id_Z == -1)
	{
		printf("Blad przy probie uzyskania id pamieci Z\n");
		return -1;
	}

    //printf("Uruchomiono proces 'robot typu Creator'.\n");
	printf("Robot_Creator: POCZATEK PRACY.\n");

	while(PRODUKCJA_TRWA)
	{
		/// sprawdzam czy zakonczyc produkcje
		if(semctl(semafor_id, LICZNIK, GETVAL, 0) == 0)
		{
			printf("Robot_Creator: KONIEC PRACY.\n");
			return 0;
		}	

		///  *** pobieram element typu X z bufora X *** ///
		/// operacja P na semaforze ZAJETE_X
		semafor.sem_num = ZAJETE_X;
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
			printf("Blad przy podlaczaniu segmentu pamieci wspoldzielonej dla procesu 'robot typu CREATOR'\n");
			return -1;
		}
		/// symuluje czas pracy
		sleep(czas_pracy);
		/// pobieram element typu X z bufora X
		produkt_koncowy[0] = bufor_X->elementy[bufor_X->pierwszy_zajety];
		bufor_X->pierwszy_zajety = (bufor_X->pierwszy_zajety + 1) % BUFOR_ROZMIAR;
		/// odlaczam segment pamieci wspoldzielonej od pamieci adresowej procesu
		if(shmdt(bufor_X) == -1)
		{
			printf("Blad przy probie odlaczenia segment pamieci wspoldzielonej dla procesu 'robot typu CREATOR'\n");
			return -1;
		}
		/// operacja V na semaforze PUSTE_X
		semafor.sem_num = PUSTE_X;
		semafor.sem_op = 1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacja an semaforze\n");
			return -1;
		}
		

		/// *** pobieram element typu Y z bufora Y *** ///
		/// operacja P na semaforze ZAJETE_Y
		semafor.sem_num = ZAJETE_Y;
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
			printf("Blad przy podlaczaniu segmentu pamieci wspoldzielonej dla procesu 'robot typu CREATOR'\n");
			return -1;
		}
		/// symuluje czas pracy
		sleep(czas_pracy);
		/// pobieram element typu Y z bufora Y
		produkt_koncowy[1] = bufor_Y->elementy[bufor_Y->pierwszy_zajety];
		bufor_Y->pierwszy_zajety = (bufor_Y->pierwszy_zajety + 1) % BUFOR_ROZMIAR;
		/// odlaczam segment pamieci wspoldzielonej od pamieci adresowej procesu
		if(shmdt(bufor_Y) == -1)
		{
			printf("Blad przy probie odlaczenia segment pamieci wspoldzielonej dla procesu 'robot typu CREATOR'\n");
			return -1;
		}
		/// operacja V na semaforze PUSTE_Y
		semafor.sem_num = PUSTE_Y;
		semafor.sem_op = 1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacja an semaforze\n");
			return -1;
		}


		/// *** pobieram element typu Z z bufora Z *** //
		/// operacja P na semaforze ZAJETE_Z
		semafor.sem_num = ZAJETE_Z;
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
			printf("Blad przy podlaczaniu segmentu pamieci wspoldzielonej dla procesu 'robot typu CREATOR'\n");
			return -1;
		}
		/// symuluje czas pracy
		sleep(czas_pracy);
		/// pobieram element typu Z z bufora Z
		produkt_koncowy[2] = bufor_Z->elementy[bufor_Z->pierwszy_zajety];
		bufor_Z->pierwszy_zajety = (bufor_Z->pierwszy_zajety + 1) % BUFOR_ROZMIAR;
		/// odlaczam segment pamieci wspoldzielonej od pamieci adresowej procesu
		if(shmdt(bufor_Z) == -1)
		{
			printf("Blad przy probie odlaczenia segment pamieci wspoldzielonej dla procesu 'robot typu CREATOR'\n");
			return -1;
		}
		/// operacja V na semaforze PUSTE_Z
		semafor.sem_num = PUSTE_Z;
		semafor.sem_op = 1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacja an semaforze\n");
			return -1;
		}

		/// dodaje znak konca napisu
		produkt_koncowy[3] = '\0';

		/// wyswietlam komunikat w konsoli o zakonczeniu produkcji napisu
		printf("*^*^* Produkcja napisu zakonczona sukcesem. Wyprodukowany napis: ** %s **^*^*\n", produkt_koncowy);

		/// operacja P na semaforze LICZNIK
		semafor.sem_num = LICZNIK;
		semafor.sem_op = -1;
		semafor.sem_flg = 0;
		if(semop(semafor_id,&semafor,1) == -1)
		{
			printf("Blad podczas wykonywania operacji na semaforze\n");
			return -1;
		}	
	}	
	return 0;
}

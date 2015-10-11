/// Przygotowal: Tomasz Bochenski
/// Opis pliku: plik wykonywalny odpalany w celu przeprowadzenia symulacji

#include "Struktury_Stale.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	struct sembuf semafor;
    int semafor_id;
    int pamiec_id_X;
    int pamiec_id_Y;
    int pamiec_id_Z;
    int liczba_robotow_X;
	int liczba_robotow_Y;
	int liczba_robotow_Z;
	int pid = 1;


    //printf("Wchodzę do funkcji main pliku SYMULACJA.\n");
	if(argc != 7)
	{
		printf("Bledna liczba argumentow dla wywolania pliku 'robot typu X'\n");
		return -1;
	}
	liczba_robotow_X = atoi(argv[1]);
	liczba_robotow_Y = atoi(argv[2]);
	liczba_robotow_Z = atoi(argv[3]);


	/// *** tworze wszystkie potrzebne semafory *** ///
	semafor_id = semget(SEMAFOR_KLUCZ, SEMAFORY_ILOSC, IPC_CREAT | IPC_EXCL | 0600);
	if(semafor_id == -1)
	{
		printf("Blad przy probie uzyskania id semaforow\n");
		return -1;
	}
    //printf("semafor_id = %d\n", semafor_id);


    /// *** ustawiam wartosci poczatkowe semaforow *** ///
    if(semctl(semafor_id, ZAJETE_X, SETVAL, 0) == -1 ||
		semctl(semafor_id, PUSTE_X, SETVAL, BUFOR_ROZMIAR) == -1 ||
		semctl(semafor_id, ZAJETE_Y, SETVAL, 0) == -1 ||
		semctl(semafor_id, PUSTE_Y, SETVAL, BUFOR_ROZMIAR) == -1 ||
		semctl(semafor_id, ZAJETE_Z, SETVAL, 0) == -1 ||
		semctl(semafor_id, PUSTE_Z, SETVAL, BUFOR_ROZMIAR) == -1 ||
		semctl(semafor_id, MUTEX_X, SETVAL, 1) == -1 ||
		semctl(semafor_id, MUTEX_Y, SETVAL, 1) == -1 ||
		semctl(semafor_id, MUTEX_Z, SETVAL, 1) == -1 ||
		semctl(semafor_id, LICZNIK, SETVAL, 10) == -1 )
	{
		printf("Blad przy probie ustawiania semaforow\n");
		return -1;
	}
	//printf("Wartosci poczatkowe wszystkich semaforow zostaly ustawione.\n");


	/// *** alokuje pamiec wspoldzielona *** ///
	/// pamiec bufora X
	pamiec_id_X = shmget(PAMIEC_X_KLUCZ, sizeof(struct Bufor),IPC_CREAT | IPC_EXCL | 0600);
	if(pamiec_id_X == -1)
	{
		printf("Blad przy probie uzyskania id pamieci X\n");
		return -1;
	}
    //printf("Pamiec wspoldzielona dla bufora X zaalokowana.\n");
	/// pamiec bufora Y
	pamiec_id_Y = shmget(PAMIEC_Y_KLUCZ, sizeof(struct Bufor), IPC_CREAT | IPC_EXCL | 0600);
	if(pamiec_id_Y == -1)
	{
		printf("Blad przy probie uzyskania id pamieci Y\n");
		return -1;
	}
    //printf("Pamiec wspoldzielona dla bufora Y zaalokowana.\n");
	/// pamiec bufora Z
	pamiec_id_Z = shmget(PAMIEC_Z_KLUCZ, sizeof(struct Bufor), IPC_CREAT | IPC_EXCL | 0600);
	if(pamiec_id_Z == -1)
	{
		printf("Blad przy probie uzyskania id pamieci Z\n");
		return -1;
	}
	//printf("Pamiec wspoldzielona dla bufora Z zaalokowana.\n");


	printf("SYMULACJA: POCZATEK.\n");

	/// *** uruchamiam procesy robotow *** ///
	int i;
	/// uruchamiam proces 'robot typu CREATOR' ///
	pid = fork();
	if(pid == 0)
	{
        char *argumenty_robot_CREATOR[] = {"./robotCreator", "1", NULL};
		execvp(argumenty_robot_CREATOR[0], argumenty_robot_CREATOR);
		return 1;
	}
	//printf("Uruchomiono proces 'robot typu Creator'.\n");
    /// uruchamiam zadana liczbe procesow 'robot typu X' ///
	for(i = 0; i < liczba_robotow_X; ++i)
	{
		pid = fork();
		if(pid == 0)
		{
		char buf[5];
		sprintf(buf,"%d",(234*i+i)%1000);
            char *argumenty_robot_X[] = {"./robotX", argv[4], buf, NULL};
			execvp(argumenty_robot_X[0], argumenty_robot_X);
			return 1;
		}
	}
    //printf("Uruchomiono procesy 'robot typu X'.\n");
	/// uruchamiam zadana liczbe procesow 'robot typu Y' ///
	for(i = 0; i < liczba_robotow_Y; ++i)
	{
		pid = fork();
		if(pid == 0)
		{
		char buf[5];
		sprintf(buf,"%d",(365*i+i)%1000);
            char *argumenty_robot_Y[] = {"./robotY", argv[5], buf, NULL};
			execvp(argumenty_robot_Y[0], argumenty_robot_Y);
			return 1;
		}
	}
    //printf("Uruchomiono procesy 'robot typu Y'.\n");
	/// uruchamiam zadana liczbe procesow 'robot typu Z' ///
	for(i = 0; i < liczba_robotow_Z; ++i)
	{
		pid = fork();
		if(pid == 0)
		{
		char buf[5];
		sprintf(buf,"%d",(123*i+i)%1000);
            char *argumenty_robot_Z[] = {"./robotZ", argv[6], buf, NULL};
			execvp(argumenty_robot_Z[0], argumenty_robot_Z);
			return 1;
		}
	}
    //printf("Uruchomiono procesy 'robot typu Z'.\n");


	while(semctl(semafor_id, LICZNIK, GETVAL, 0) != 0);

	/// podnosze wszystkie semafory
	semafor.sem_num = PUSTE_X;
	semafor.sem_op = liczba_robotow_X;
	semafor.sem_flg = 0;
	if(semop(semafor_id,&semafor,1) == -1)
	{
		printf("Blad podczas wykonywania operacja an semaforze\n");
		return -1;
	}

	semafor.sem_num = PUSTE_Y;
	semafor.sem_op = liczba_robotow_Y;
	semafor.sem_flg = 0;
	if(semop(semafor_id,&semafor,1) == -1)
	{
		printf("Blad podczas wykonywania operacja an semaforze\n");
		return -1;
	}

	semafor.sem_num = PUSTE_Z;
	semafor.sem_op = liczba_robotow_Z;
	semafor.sem_flg = 0;
	if(semop(semafor_id,&semafor,1) == -1)
	{
		printf("Blad podczas wykonywania operacja an semaforze\n");
		return -1;
	}


	int status;
	for(i = 0; i < liczba_robotow_X+liczba_robotow_Y+liczba_robotow_Z+1; ++i)
		wait(&status);

    /// *** usuwam semafory oraz zaalokowana pamiec wspoldzielona *** ///
	semctl(semafor_id, 0, IPC_RMID);
	shmctl(pamiec_id_X, IPC_RMID, NULL);
	shmctl(pamiec_id_Y, IPC_RMID, NULL);
	shmctl(pamiec_id_Z, IPC_RMID, NULL);

	printf("SYMULACJA: KONIEC.\n");


	return 0;
}

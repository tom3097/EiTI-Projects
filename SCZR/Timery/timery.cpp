#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/siginfo.h>


/**
 * Stale definiujace pulsy uzytkownika
 */
#define T2_PULSE _PULSE_CODE_MINAVAIL+1
#define T3_PULSE _PULSE_CODE_MINAVAIL+2

/**
 * Deklaracja zmiennych globalnych 
 */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //< inicjalizacja mutexa
timer_t T1, T2, T3, T4;
int channelId, connectionId;

/**
 * Lancuchy znakow wypisywane jako komunikaty na konsoli
 */
char* T1_comm = "Timer T1";
char* T2_comm = "Timer T2";
char* T3_comm = "Timer T3";
char* T4_comm = "Timer T4. Finishing program.";

/**
 * struktury reprezentujace czas rozpoczacia programu oraz liczbe sekund i milisekund
 * ktore minely od poczatku wykonywania programu
 */
struct timeval begin_time, program_time;

/**
 * Funkcja sluzaca do wypisywania komunikatow informujacych
 * o czasie i timerze. Obiekt wspoldzielony przez watki (konsola)
 * jest chroniona mutexem.
 * @param name - lancuch znakow informujacy o id timera
 */
void printCommunicate(char* name) {
  time_t curr_time = time(NULL);
  gettimeofday(&program_time, NULL);
  
  // Dopelnienie do sekundy jesli liczba milisekund w obecnym czasie jest mniejsza niz 
  // na poczatku programu
  if(program_time.tv_usec >= begin_time.tv_usec) {
    program_time.tv_usec = program_time.tv_usec - begin_time.tv_usec;
  }
  else {
    --program_time.tv_sec;
    program_time.tv_usec = program_time.tv_usec + 1000000 - begin_time.tv_usec;
  }
  
  program_time.tv_sec = program_time.tv_sec - begin_time.tv_sec;
  //Blokujemy mutex i wypisujemy komunikat
  pthread_mutex_lock(&mutex);
  printf("%s %s: %u.%02u\n", ctime(&curr_time), name, program_time.tv_sec, program_time.tv_usec);
  fflush(stdout);
  pthread_mutex_unlock(&mutex);
}

/**
 * Handler obslugujacy sugnal uzytkownika
 * @param value - nieuzywany, aby zachowac zgodnosc
 */
void handle_signal(int value) {
  printCommunicate(T4_comm);
  
  timer_delete(T1);
  timer_delete(T2);
  timer_delete(T3);
  timer_delete(T4);
  
  ConnectDetach(connectionId);
  ChannelDestroy(channelId);
  
  exit(0);
}

/**
 * Watek dla timera 1
 * @param val - nie uzywane, aby zachowac zgodniosc
 */
void T1_thread(union sigval val) {
  printCommunicate(T1_comm);
}

/**
 * Pomocnicza funkcja uzupelniajaca strukture itimerspec
 * @param tspec - wskaznik do struktury uzupelnianej
 * @param itValSec - sekundy po jakich timer ma byc uruchomiony
 * @param itValNsec - nanosekundy po jakich timer ma byc uruchomiony
 * @ param itInSec - sekundy pomiedzy cyklami
 * @ param itInNsec - nanosekundy pomiedzy cyklami
 */
void getitimespec(struct itimerspec* tspec, long itValSec, long itValNsec, long itInSec, long itInNsec) {
  //struct itimerspec tspec;
  tspec->it_value.tv_sec = itValSec;
  tspec->it_value.tv_nsec = itValNsec;
  tspec->it_interval.tv_sec = itInSec;
  tspec->it_interval.tv_nsec = itInNsec;
}

/**
 * Funkcja do tworzenie timerow tworzacych nowe watki
 * @param timer - id timera
 * @param fun - wskaznik na funkcje wykonywana podczas eventu
 * @param itValSec - sekundy po jakich timer ma byc uruchomiony
 * @param itValNsec - nanosekundy po jakich timer ma byc uruchomiony
 * @ param itInSec - sekundy pomiedzy cyklami
 * @ param itInNsec - nanosekundy pomiedzy cyklami
 */
void create_thread_timer(timer_t* timer, void (*fun)(union sigval), long itValSec, long itValNsec, long itInSec, long itInNsec) {
  struct sigevent event;
  struct itimerspec tspec;
  
  SIGEV_THREAD_INIT(&event, fun, NULL, NULL);
  timer_create(CLOCK_REALTIME, &event, timer);
  getitimespec(&tspec, itValSec, itValNsec, itInSec, itInNsec);
  timer_settime(*timer, 0, &tspec, NULL);
}


/**
 * Funkcja do tworzenie timerow generujacych impulsy
 * @param timer - id timera
 * @param pulse_code - kod charakteryzujacy puls
 * @param itValSec - sekundy po jakich timer ma byc uruchomiony
 * @param itValNsec - nanosekundy po jakich timer ma byc uruchomiony
 * @ param itInSec - sekundy pomiedzy cyklami
 * @ param itInNsec - nanosekundy pomiedzy cyklami
 */
void create_pulse_timer(timer_t* timer, int pulse_code, long itValSec, long itValNsec, long itInSec, long itInNsec) {
  struct sigevent event;
  struct itimerspec tspec;
  
  SIGEV_PULSE_INIT(&event, connectionId, SIGEV_PULSE_PRIO_INHERIT, pulse_code, 0);
  timer_create(CLOCK_REALTIME, &event, timer);
  getitimespec(&tspec, itValSec, itValNsec, itInSec, itInNsec);
  timer_settime(*timer, 0, &tspec, NULL);
}

/**
 * Funkcja do tworzenie timerow generujacych sygnaly
 * @param timer - id timera
 * @param sigcode - numer charakteryzujacy rodzaj sygnalu
 * @param itValSec - sekundy po jakich timer ma byc uruchomiony
 * @param itValNsec - nanosekundy po jakich timer ma byc uruchomiony
 * @ param itInSec - sekundy pomiedzy cyklami
 * @ param itInNsec - nanosekundy pomiedzy cyklami
 */
void create_signal_timer(timer_t* timer, int sigcode, long itValSec, long itValNsec, long itInSec, long itInNsec) {
  struct sigevent event;
  struct itimerspec tspec;
  
  SIGEV_SIGNAL_INIT(&event, sigcode);
  timer_create(CLOCK_REALTIME, &event, timer);
  getitimespec(&tspec, itValSec, itValNsec, itInSec, itInNsec);
  timer_settime(*timer, 0, &tspec, NULL);
}

/**
 * Funkcja sluzaca do odbierania pulsow i odpowiedniego reagowania na nie
 */
void receive_pulses() {
  int rcvid;
  struct _pulse message;
  
  // w petli odbieramy wiadomosci oraz wyswietlamy odpowiedni komunikat
  // w zaleznosci od rodzaju pulsu
  while(1)
  {
    rcvid = MsgReceive(channelId, &message, sizeof(message), NULL);
    
    if(rcvid == 0 && message.code == T2_PULSE) {
      printCommunicate(T2_comm);
    }
    else if(rcvid == 0 && message.code == T3_PULSE) {
      printCommunicate(T3_comm);
    }
  }
}


int main() {

  // Tworzymy kanal. Gdy tworzenie sie nie uda konczymy program
  if((channelId = ChannelCreate(0)) == -1) {
    printf("Error when creating channel.\n");
    exit(-1);
  }
  
  // Tworzymy polaczenie z kanalem. Gdy tworzenie sie nie uda konczymy program.
  if((connectionId = ConnectAttach(0, 0, channelId, 0, 0)) == -1) {
    printf("Error when creating connection.\n");
    exit(-1);
  }
  
  // Dodajemy akcje reagujaca na okreslony sygnal
  signal(SIGUSR1, handle_signal);
  
  gettimeofday(&begin_time, NULL);
  
  // Tworzymy wszystkie timery
  create_thread_timer(&T1, T1_thread, 0, 500000000, 0, 500000000);
  create_pulse_timer(&T2, T2_PULSE, 2, 0, 2, 0);
  create_pulse_timer(&T3, T3_PULSE, 5, 0, 1, 0);
  create_signal_timer(&T4, SIGUSR1, 10, 0, 0, 0);
  
  // Uruchamiamy funkcje odbierajaca pulsy.
  receive_pulses();
  
  return 0;
}
#/** PhEDIT attribute block
#-10:70
#**  PhEDIT attribute block ends (-0000083)**/

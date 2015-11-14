// cout
#include <iostream>
//errno
#include <errno.h>
//perror
#include <stdio.h>
// srand, rand
#include <cstdlib>
// time
#include <ctime>
// pthread_id, pthread_create, pthread_join, pthread_cond_wait, pthread_cond_signal, pthread_mutex_lock, pthread_mutex_unlock
#include <pthread.h>
//string
#include <string>
// ostringstream
#include <sstream>

// stala opisujaca rozmiar bufora
const int BUF_SIZE = 5;
// stala opisujaca czas produkcji elementu A
const int MAN_TIME_A = 1;
// stala opisujaca czas produkcji elementu B
const int MAN_TIME_B = 2;
// stala opisujaca czas konsumpcji
const int CON_TIME = 4;

// mutex chroniacy dostepu do bufora A
pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
// mutex chroniacy dostepu do bufora B
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;
// zmienna warunkowa sluzaca do usypiania producentow A
pthread_cond_t man_cond_A = PTHREAD_COND_INITIALIZER;
// zmienna warunkowa sluzaca do usypiania producentow B
pthread_cond_t man_cond_B = PTHREAD_COND_INITIALIZER;
// zmienna warunkowa sluzaca do usypiania konsumentow pobierajacych A
pthread_cond_t con_cond_A = PTHREAD_COND_INITIALIZER;
// zmienna warunkowa sluzaca do usypiania konsumentow pobierajacych B
pthread_cond_t con_cond_B = PTHREAD_COND_INITIALIZER;

// mutex chroniacy dostepu do ekranu
pthread_mutex_t screenLocker = PTHREAD_MUTEX_INITIALIZER;

// szablon funkcji sluzacy do konwersji dowolnego typu na string
template<typename T>
std::string toString(T val)
{
  std::ostringstream ss;
  ss<<val;
  return ss.str();
}

// klasa sluzaca do bezpiecznego wypisywania tekstu na konsoli
class Display
{
public:
  static void printMessage(std::string& msg)
  {
    pthread_mutex_lock(&screenLocker);
    std::cout<<msg;
    pthread_mutex_unlock(&screenLocker);
  }
};
 
// klasa Buffer reprezentujaca bufor cykliczny
class Buffer
{
  // tablica w ktorej przechowywane sa produkty
  int depot[BUF_SIZE];
  // aktualna liczba elementow w tablicy
  int size;
  // indeks pierwszego wolnego miejsca w tablicy
  int first_empty;
  // indeks pierwszego zajetego miejsca w tablicy
  int first_full;
public:
  Buffer()
  {
    size = 0;
    first_empty = 0;
    first_full = 0;
  }
  // metoda sprawdzajaca czy w buforze cyklicznym jest jakiekolwiek wolne miejsce
  // zwraca true jesli tak, w przeciwnym przypadku zwraca false
  bool hasEmptyPlace()
  {
    if(size != BUF_SIZE)
      return true;
    return false;
  }
  // metoda sprawdzajaca czy w buforze cyklicznym jest jakiekolwiek pelne miejsce
  // zwraca true jesli tak, w przeciwnym przypadku zwraca false
  bool hasFullPlace()
  {
    if(size != 0)
      return true;
    return false;
  }
  // metoda wkladajaca element do bufora cyklicznego
  void push(int val)
  {
    depot[first_empty] = val;
    first_empty = (first_empty + 1) % BUF_SIZE;
    ++size;
  }
  // metoda pobierajaca element z bufora cyklicznego
  int pop()
  {
    int to_return = depot[first_full];
    first_full = (first_full + 1) % BUF_SIZE;
    --size;
    return to_return;
  }
  // metoda zwracajaca aktualny rozmiar bufora cyklicznego
  int getSize()
  {
    return size;
  }
};

Buffer bufferA;
Buffer bufferB;

// funkcja reprezentujaca producenta A
void* manufacturerA(void*)
{
  while(true)
  {
    sleep(MAN_TIME_A);
    // blokujemy mutex odpowiedzialny za dostep do bufora cyklicznego A
    pthread_mutex_lock(&mutexA);
    // dopoki caly bufor A jest pelny zawieszamy producenta na zmiennej warunkowej
    while(!bufferA.hasEmptyPlace())
    {
      std::string message = "[Producent A] nie dodano produktu - bufor A pelny\n";
      Display::printMessage(message);
      pthread_cond_wait(&man_cond_A, &mutexA);
    }
    int product = rand()%1000;
    bufferA.push(product);
    std::string message = "[Producent A] dodano produkt: " +toString(product) + " (" + toString(bufferA.getSize()) + ")\n";
    Display::printMessage(message);
    // sygnalizujemy konsumentowi ze w buforze A pojawil sie produkt
    pthread_cond_signal(&con_cond_A);
    // odblokowujemy mutex odpowiedzialny za dostep do bufora cyklicznego A
    pthread_mutex_unlock(&mutexA);
  }
}

// funkcja reprezentujaca producenta B
void* manufacturerB(void*)
{
  while(true)
  {
    sleep(MAN_TIME_B);
    // blokujemy mutex odpowiedzialny za dostep do bufora cyklicznego B
    pthread_mutex_lock(&mutexB);
    // dopoki caly bufor B jest pelny zawieszamy producenta na zmiennej warunkowej
    while(!bufferB.hasEmptyPlace())
    {
      std::string message = "[Producent B] nie dodano produktu - bufor B pelny\n";
      Display::printMessage(message);
      pthread_cond_wait(&man_cond_B, &mutexB);
    }
    int product = rand()%1000;
    bufferB.push(product);
    std::string message = "[Producent B] dodano produkt: " +toString(product) + " (" + toString(bufferB.getSize()) + ")\n";
    Display::printMessage(message);
    // sygnalizujemy konsumentowi ze w buforze B pojawil sie produkt
    pthread_cond_signal(&con_cond_B);
    // odblokowujemy mutex odpowiedzialny za dostep do bufora cyklicznego B
    pthread_mutex_unlock(&mutexB);
  }
}
     
// funkcja reprezentujaca konsumenta
void* consumer(void*)
{
  while(true)
  {
    sleep(CON_TIME);
    // blokujemy mutex odpowiedzialny za dostep do bufora cyklicznego A
    pthread_mutex_lock(&mutexA);
    // dopoki caly bufor A jest pusty zawieszamy konsumenta na zmiennej warunkowej
    while(!bufferA.hasFullPlace())
    {
      std::string message = "[Konsument] nie pobrano produktu A i B - bufor A pusty\n";
      Display::printMessage(message);
      pthread_cond_wait(&con_cond_A, &mutexA);
    }
    // blokujemy mutex odpowiedzialny za dostep do bufora cyklicznego B
    pthread_mutex_lock(&mutexB);
    // dopoki caly bufor B jest pusty zawieszamy konsumenta na zmiennej warunkowej
    while(!bufferB.hasFullPlace())
    {
      std::string message = "[Konsument] nie pobrano produktu A i B - bufor B pusty\n";
      Display::printMessage(message);
      pthread_cond_wait(&con_cond_B, &mutexB);
    }
    int productA = bufferA.pop();
    int productB = bufferB.pop();
    std::string message = "pobrano produkty A: " + toString(productA) + " i produkt B: " + toString(productB) + "(" + toString(bufferA.getSize()) + " " + toString(bufferB.getSize()) + ")\n";
    Display::printMessage(message);
    // sygnalizujemy producentow o zwolnieniu miejsca
    pthread_cond_signal(&man_cond_A);
    pthread_cond_signal(&man_cond_B);
    // zwalniamy oba mutexy
    pthread_mutex_unlock(&mutexA);
    pthread_mutex_unlock(&mutexB);
  }
}

int main()
{
  srand(time(NULL));
  
  // tworzymy id watkow producentow i konsumentow
  pthread_t man_A_id, man_B_id;
  pthread_t con_id[2];
  
  // startujemy watek producenta A
  errno = pthread_create(&man_A_id, NULL, manufacturerA, NULL);
  if(errno)
  {
    perror("pthread_create");
    return EXIT_FAILURE;
  }
  
  // startujemy watek producenta B
  errno = pthread_create(&man_B_id, NULL, manufacturerB, NULL);
  if(errno)
  {
    perror("pthread_create");
    return EXIT_FAILURE;
  }
  
  // startujemy watek konsumentow
  for(int i = 0; i < 2; ++i)
  {
    errno = pthread_create(&con_id[i], NULL, consumer, NULL);
    if(errno)
    {
      perror("pthread_create");
      return EXIT_FAILURE;
    }
  }
  
  // wstrzymujemy wykonywanie glownego watku do czasu zakonczenia
  // watkow producentow i watkow konsumentow
  pthread_join(man_A_id, NULL);
  pthread_join(man_B_id, NULL);
  for(int i = 0; i < 2; ++i)
    pthread_join(con_id[i], NULL);
  
  return 0;  
}
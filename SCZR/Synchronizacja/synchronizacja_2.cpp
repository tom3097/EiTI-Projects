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

// stala opisujaca rozmiar bufora
const int BUF_SIZE = 5;
// stala opisujaca czas produkcji
const int MAN_TIME = 3;
// stala opisujaca czas konsumpcji
const int CON_TIME = 5;


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

// tworzymy bufor cykliczny jako zmienna globalna
// watki korzystaja z wspolnej przestrzeni adresowej
Buffer buffer;
// tworzymy i inicjujemy mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// tworzymy i inicjujemy zmienna warunkowa dla producenta
pthread_cond_t man_cond = PTHREAD_COND_INITIALIZER;
// tworzymy i inicjujemy zmienna warunkowa dla konsumenta
pthread_cond_t con_cond = PTHREAD_COND_INITIALIZER;


// funkcja reprezentujaca producenta
void* manufacturer(void*)
{
  while(true)
  {
    sleep(MAN_TIME);
    // blokujemy mutex odpowiedzialny za dostep do bufora cyklicznego
    pthread_mutex_lock(&mutex);
    // dopoki caly bufor jest pelny zawieszamy producenta na zmiennej warunkowej
    while(!buffer.hasEmptyPlace())
    {
      std::cout<<"[Producent] nie dodano produktu - bufor pelny\n";
      pthread_cond_wait(&man_cond, &mutex);
    }
    int product = rand()%1000;
    buffer.push(product);
    std::cout<<"[Producent] dodano produkt: "<<product<<" ("<<buffer.getSize()<<")\n";
    // sygnalizujemy konsumentowi ze w buforze pojawil sie produkt
    pthread_cond_signal(&con_cond);
    // odblokowujemy mutex odpowiedzialny za dostep do bufora cyklicznego
    pthread_mutex_unlock(&mutex);
  }
}
     
// funkcja reprezentujaca konsumenta
void* consumer(void*)
{
  while(true)
  {
    sleep(CON_TIME);
    // blokujemy mutex odpowiedzialny za dostep do bufora cyklicznego
    pthread_mutex_lock(&mutex);
    // dopoki caly bufor jest pusty zawieszamy konsumenta na zmiennej warunkowej
    while(!buffer.hasFullPlace())
    {
      std::cout<<"[Konsument] nie pobrano produktu - bufor pusty\n";
      pthread_cond_wait(&con_cond, &mutex);
    }
    int product = buffer.pop();
    std::cout<<"[Konsument] pobrano produkt: "<<product<<"("<<buffer.getSize()<<")\n";
    // sygnalizujemy producentowi ze zwolnilo sie miejsce w buforze
    pthread_cond_signal(&man_cond);
    // odblokowujemy mutex odpowiedzialny za dostep do bufora cyklicznego
    pthread_mutex_unlock(&mutex);
  }
}

int main()
{
  srand(time(NULL));
  
  // tworzymy id watkow producenta i konsumenta
  pthread_t man_id, con_id;
  
  // startujemy watek producenta
  errno = pthread_create(&man_id, NULL, manufacturer, NULL);
  if(errno)
  {
    perror("pthread_create");
    return EXIT_FAILURE;
  }
  
  // startujemy watek konsumenta
  errno = pthread_create(&con_id, NULL, consumer, NULL);
  if(errno)
  {
    perror("pthread_create");
    return EXIT_FAILURE;
  }
  
  // wstrzymujemy wykonywanie glownego watku do czasu zakonczenia
  // watku producenta i watku konsumenta
  pthread_join(man_id, NULL);
  pthread_join(con_id, NULL);
  
  return 0;  
}
  
      









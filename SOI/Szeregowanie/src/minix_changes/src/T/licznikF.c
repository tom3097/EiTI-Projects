#include <stdlib.h>
#include <lib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  int liczba;
  message m;
  
  liczba = _syscall(MM,GETSIZEF,&m);
  printf("Aktualna liczba procesow w kolejce: %d\n",liczba);
  return 0;
}

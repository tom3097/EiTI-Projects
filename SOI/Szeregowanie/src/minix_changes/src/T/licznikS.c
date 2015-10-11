#include <stdio.h>
#include <stdlib.h>
#include <lib.h>

int main(int argc, char* argv[])
{
  message m;
  int liczba;

  liczba = _syscall(MM,GETSIZES,&m);
  printf("Aktualna liczba procesow w kolejce: %d\n", liczba);

  return 0;
}

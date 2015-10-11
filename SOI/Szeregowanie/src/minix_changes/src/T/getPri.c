#include <stdio.h>
#include <stdlib.h>
#include <lib.h>

int main(int argc, char* argv[])
{
  message m;
  int numer;
  m.m1_i1 = atoi(argv[1]);

  numer = _syscall(MM,GETPRI,&m);

  printf("PID: %d, NUMER: %d\n", atoi(argv[1]), numer);

  return 0;
}

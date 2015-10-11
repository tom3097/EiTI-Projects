#include <stdio.h>
#include <stdlib.h>
#include <lib.h>

int main(int argc, char* argv[])
{
  message m;
  int numer;

  m.m1_i1 = atoi(argv[1]);
  m.m2_i2 = atoi(argv[2]);

  numer = _syscall(MM,SETPRI,&m);

  printf("Numer: %d",numer);
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <lib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  int nr_kol;
  int pid;
  int number;
  int i;
  message m;

  number = atoi(argv[1]);
  pid = getpid() - number;
  nr_kol = 1;

  for(i = 0; i < number; ++i)
  {
    m.m1_i1 = pid;
    m.m1_i2 = nr_kol;

    _syscall(MM,SETPRI,&m);

    pid++;
    nr_kol = (nr_kol%5) + 1;
  }

  return 0;
}   

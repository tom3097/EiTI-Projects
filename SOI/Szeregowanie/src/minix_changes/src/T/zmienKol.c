#include <stdlib.h>
#include <stdio.h>
#include <lib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  int aux_pid;
  int number;
  int i;
  int nr_kol;
  message m;

  number = atoi(argv[1]);
  aux_pid = getpid();
  aux_pid = aux_pid - number;
  nr_kol = 1;

  for(i = 0; i < number; i++)
  {
    m.m1_i1 = aux_pid;
    m.m1_i2 = nr_kol;
    _syscall(MM,SETPRI,&m); 

    aux_pid++;
    nr_kol = (nr_kol)%3 + 1;
  }
  
  return 0;
}    
  

  

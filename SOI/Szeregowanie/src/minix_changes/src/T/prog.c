#include <stdio.h>
#include <stdlib.h>
#include <lib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
  clock_t start;
  clock_t stop;
  int zew;
  int wew;
  int i;
  int j;

   
  zew = 1000;
  wew = 1000000;

  for(i = 0; i < zew; i++)
    for(j = 0; j < wew; ++j);
  
  printf("\nProgram p o pid: %d zostal zakonczony\n",getpid());
  return 0;
}      

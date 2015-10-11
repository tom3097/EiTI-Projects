#include <stdio.h>
#include <stdlib.h>
#include <lib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  printf("PID: %d\n",(int)getpid());
  return 0;
} 

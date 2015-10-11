#include <stdio.h>
#include <stdlib.h>
#include <lib.h>

int main(int argc, char* argv[])
{
  message m;

  int numerH;
  int pidH;

  numerH = _syscall(MM,GETHEADNR,&m);
  pidH = _syscall(MM,GETHEADPID,&m);

  printf("HEAD pid: %d, num: %d\n",pidH, numerH);

  return 0;
}

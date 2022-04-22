#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/*
void manejador_senial(int a){
   
}
*/

int main ()
{
  signal(SIGKILL, SIG_IGN);
   //signal(SIGSTOP, SIG_IGN);  //Ctrl + Z
   
   printf("Proceso PID = %d\n", getpid());   
   
   while(1);
   
   exit(0);
}

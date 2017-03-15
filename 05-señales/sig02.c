/*
 * Ejercicios 3 y 4 de TP Seniales
*/

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
   //signal(SIGTSTP, SIG_IGN);  //Ctrl + z
   
   printf("Proceso PID = %d\n", getpid());   
   
   while(1);
   
   exit(0);
}

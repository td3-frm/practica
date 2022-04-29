/*
 * Ejercicio 1 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <signal.h>

#define WRITE 1 
#define READ 0
 
void manejador(int a)
{
   printf ("SIGPIPE\n");
}

int main (){

   pid_t pid;
   int fd[2];
   int leido;
   char buff[80];

   signal(SIGPIPE, manejador);
   
   pipe(fd);

   printf ("fd[0] = %d fd[1] = %d \n ", fd[0], fd[1]);   

   pid = fork();

   if (pid == 0 ){ 
      
      // Se cierra el lado de escritura del hijo
      close(fd[WRITE]);  
	
      leido = read(fd[READ], buff, sizeof(buff));
      
      if(leido < 1)
      {
         printf("Hijo, tuberia vacía\n");
         printf("leido = %d\n", leido);
      }
      else 
      {
         // Escribe en consola
         //~ printf("Hijo, leido de la tuberia \"%s\" por el proceso hijo, pid %d \n", buff, getpid());
         write (STDOUT_FILENO, "Hijo, leido de la tuberia \"", sizeof("Hijo, leido de la tuberia \""));
         write (STDOUT_FILENO, buff, leido);
         printf("\" por el proceso hijo, pid %d \n", getpid());
      }
      
      close(fd[READ]);
      
      exit(0);
   
   }else
   {
	   // Se cierra el lado de lectura del padre
	   close(fd[READ]);
	   
	   printf("Ingrese una cadena de caracteres por consola: \n");
	   // Se lee por consola
	   leido = read(STDIN_FILENO, buff, sizeof(buff));

	   // Se escribe en la tuberia
	   write(fd[WRITE], buff, leido-1);
	   
	   // Se cierra el lado de escritura. 
	   close(fd[WRITE]);

	   wait(NULL);   
	   
	   //~ printf("Padre, escrito en la tuberia \"%s\" por el proceso padre, pid %d \n", buff, getpid());
	   write (STDOUT_FILENO, "Padre, escrito en la tuberia \"", sizeof("Padre, Escrito en la tuberia \""));
	   write (STDOUT_FILENO, buff, leido-1);
	   printf("\" por el proceso padre, pid %d \n", getpid());
	
	   exit(0);
   }

}

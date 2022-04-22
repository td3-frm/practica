/*
 * Ejercicio 1 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 


int main (){

   pid_t pid;
   int ipc[2];
   int leido;
   char buff[80];

   pipe(ipc);

   printf ("ipc[0] = %d ipc[1] =%d \n ", ipc[0], ipc[1]);   

   pid = fork();

   if (pid == 0 ){ 
      
      // Se cierra el lado de escritura del hijo
      close(ipc[1]);
      
      leido = read(ipc[0], buff, sizeof(buff));
      if(leido < 1){
         write (STDOUT_FILENO, "Error al leer tuberia\n", sizeof("Error al leer tuberia\n"));
      }else {

         // Escribir en consola
         write (STDOUT_FILENO, "Leido de la tuberia \"", sizeof("Leido de la tuberia \""));
         write (STDOUT_FILENO, buff, leido-1);
         printf("\" por el proceso hijo, pid %d \n", getpid());
      }
      exit(0);
   
   }else{
	   // Se cierra el lado de lectura del padre
	   close(ipc[0]);
	   
	   printf("Ingrese una cadena de caracteres por consola: \n");
	   // Se lee por consola
	   leido = read(STDIN_FILENO, buff,  sizeof(buff));

	   // Se escribe en la tuberia
	   write(ipc[1], buff, leido);
	   
	   // Se cierra el lado de escritura. 
	   close(ipc[1]);

	   wait(NULL);   
	   write (STDOUT_FILENO, "Escrito en la tuberia \"", sizeof("Escrito en la tuberia \""));
	   write (STDOUT_FILENO, buff, leido-1);
	   printf("\" por el proceso padre, pid %d \n", getpid());

	   exit(0);
   }

}

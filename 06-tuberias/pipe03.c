/*
 * Ejercicio 3 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 

#define FRASE_A "INFORMACION IMPORTANTE A"
#define FRASE_B "INFORMACION IMPORTANTE B"
#define BUFF_SIZE 80

void pipe_sign_handler(int a){
   
   write (STDOUT_FILENO, "Problema con pipeline\n ", sizeof("Problema con pipeline\n"));
   exit(-1);
}

int main (){

   int ipc[2], proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   signal(SIGPIPE, pipe_sign_handler);
   
   pipe(ipc);

   switch (fork()){ 
      
      case 0:
		  close(ipc[0]);      
		  strncpy(buff, FRASE_A, sizeof(FRASE_A)); 
		  write(ipc[1], buff, sizeof(FRASE_A));
		  exit(0);
      break;
      
      default:
      switch (fork()){ 
            
         case 0:
            close(ipc[0]);               
            strncpy(buff, FRASE_B, sizeof(FRASE_B)); 
            write(ipc[1], buff,    sizeof(FRASE_B));
            exit(0);      
         break;
         
         default:
            close(ipc[1]);
            int i;
            for(i=0; i<2; i++){
               leido = read(ipc[0], buff, sizeof(buff));
               if(leido < 1){
                  write (STDOUT_FILENO, "Error al leer tuberia\n", sizeof("Error al leer tuberia\n"));
               }else {
                  write (STDOUT_FILENO, "Leido de la tuberia \"", sizeof("Leido de la tuberia \""));
                  write (STDOUT_FILENO, buff, leido-1);
                  printf("\" por el proceso padre\n.");
               }
            }

            close(ipc[0]);
            wait(NULL);
            wait(NULL);
            exit(0);
         break;
      }
   }   
}

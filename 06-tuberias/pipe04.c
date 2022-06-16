/*
 * Ejercicio 4 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 

#define DATA "TECNICAS DIGITALES III ES LO MAS"
#define ERROR "SIGPIPE, problema con pipeline.\n "
#define BUFF_SIZE 80

void pipe_sign_handler(int a){
   
   write (STDOUT_FILENO, ERROR, sizeof(ERROR));
   exit(-1);
}

int main (){

   int ipc[2];
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   signal(SIGPIPE, pipe_sign_handler);
   
   if (pipe(ipc) == -1)
      exit(-1);
   
   close(ipc[0]);
   
   switch (fork()){ 
      
      case 0:
         close(ipc[1]);
         printf("Hijo leyendo tuberia... \n");
         leido = read(ipc[0], buff, sizeof(buff));
         if(leido < 1){
            write(STDOUT_FILENO, "Error al leer tuberia\n", sizeof("Error al leer tuberia\n"));
         }else {
            write(STDOUT_FILENO, "Leido de la tuberia \"", sizeof("Leido de la tuberia \""));
            write(STDOUT_FILENO, buff, leido-1);
            printf("\" por el proceso hijo.\n");
         }
         exit(0);
         
      default:
         strncpy(buff, DATA, sizeof(DATA));
         write(ipc[1], buff, sizeof(DATA));
         wait(NULL);      
         exit(0);      
   }
}

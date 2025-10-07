/*
 * PARCIAL 1: programa para ser ejecutado en el proceso padre.
 * 
 * Comando para compilar:
 * 
 * 	gcc -c padre.c && gcc hijo.o padre.o -o padre

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define MENSAJE "HOLA HIJA MIA"

int hijo (int fd[2]);

int main(void) 
{
	int fd[2];
	int pid;
	char tx_buffer[20] = MENSAJE;
	
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return -1;
    }
    
    if ((pid = fork()) == -1)
    {
        perror("fork");
        return -1;
    }
    
// codigo que ejecuta el hijo
	if (pid==0) 
	{ 
        hijo(fd);

        return 0;
    }
// codigo que ejecuta el padre   
	else
	{
		printf("Proceso Padre en ejecucion... \n"); 
		
		sleep(1);
				
		// **** RESOLUCION DEL EJERCICIO *******************************
    
		// *************************************************************
		
		wait(NULL);  
		exit(0);
	}
}

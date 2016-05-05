/*
 * Ejercicio 4 de la guía práctica Tuberías
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#define DATA "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

void pipe_sign_handler(int a){
	
	printf("\nProblema con pipeline.\n");
	exit(-1);
}

int main (){

	int ipc[2], proc;
	int leido, success;
	char buff[BUFF_SIZE] = {0};

	signal(SIGPIPE, pipe_sign_handler);
	
	if (pipe(ipc) == -1)
		exit(-1);
	
	close(ipc[0]);
	
	switch (fork()){ 
		
		case 0:
			//close(ipc[0]);
			printf("Leyendo tuberia... \n");
			leido = read(ipc[0], buff, sizeof(buff));

			write (0, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
			write (0, buff, leido-1);
			printf(", por el proceso hijo, pid %d \n", getpid());
			exit(0);		
			
		default:
			//close(ipc[0]);
			strncpy(buff, DATA, sizeof(DATA)); 
			write(ipc[1], buff, sizeof(DATA));
			//exit(0);
		
			wait(NULL);		
			
			return 0;		
	}
}

/*
 * Ejercicio 2 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

pid_t pid;
int i;

int main (){

<<<<<<< HEAD
	pid_t pid;
	int i;

	pid = fork();
	
	if (pid == 0) 
		printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
	else
		printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
	
=======
	printf ("Proceso unico: Mi pid es %d\n", getpid());
	
	pid = fork();		
	printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
		
>>>>>>> 242b4904c0f15933c5411db1a1ef1eb693788013
	// Ejecute pstree en otra consola	
	sleep(30); 
	
	exit(0);
	
}

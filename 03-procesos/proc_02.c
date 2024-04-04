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

	printf ("Proceso unico: Mi pid es %d\n", getpid());
	
	pid = fork();		
	printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
		
	// Ejecute pstree en otra consola	
	sleep(30); 
	
	exit(0);
	
}

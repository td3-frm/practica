/*
 * Ejercicio 2 de la guía práctica Procesos
*/
#include <stdio.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid
#include <signal.h>

int main (){

	pid_t pid;
	int i;
	
	pid = fork();		
	printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
		
	// Ejecute pstree en otra consola	
	sleep(30); 
	
	return 0;
}

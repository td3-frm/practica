/*
 * Ejercicio 3 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

pid_t pid1,pid2;

int main (){

	printf ("0-Proceso unico: Mi pid es %d y voy a ejecutar 2 fork()\n", getpid());
	
	pid1=fork();
	printf ("1-Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid1);

	pid2=fork();
	printf ("2-Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid2);

	sleep(30); // Probar con el comando pstree -p
	
	exit(0);

}

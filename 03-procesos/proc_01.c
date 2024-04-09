/*
 * Ejercicio 1 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){
	
	printf ("Proceso unico: Mi pid es %d y el pid de papa es %d\n", getpid(),getppid());

	exit(0);   
}

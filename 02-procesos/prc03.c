/*
 * Ejercicio 3 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){
	
	fork();
	fork();
	printf ("Mi pid es %d y el pid de papa es %d\n", getpid(),getppid());
	sleep(30); // Probar con el comando pstree -p
	exit(0);

}

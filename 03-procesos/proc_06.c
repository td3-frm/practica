/*
 * Ejercicio 6 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main ()
{
	int x = 100;
	
	printf("Soy el proceso: %d \n ",getpid());
	
	switch (fork())
	{
		case -1:   // No pudo crear el proceso
			printf ("Error. No se crea proceso hijo");
			break;

		case 0:   //proceso hijo
			printf ("Soy el hijo, pid: %d, x = %d, dicección X=%li\n", getpid(), --x,(&x));
			break;

		default:  //proceso padre
			printf ("Soy el padre, pid: %d, x = %d, dicección X=%li\n", getpid(), ++x,(&x));
	}
    exit(0);

}

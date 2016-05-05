/*
 * Ejercicio 5 de la guía práctica Procesos
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

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
			printf ("Soy el proceso hijo, pid: %d , x = %d\n", getpid(), --x);
			break;

		default:  //proceso padre
			printf ("Soy el proceso padre, pid: %d , x = %d\n", getpid(), ++x);
	}
    return 0;

}

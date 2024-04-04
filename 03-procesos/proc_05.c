/*
 * Ejercicio 5 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

pid_t pid;

int main (){

    printf ("Unico proceso antes del fork(), con pid %d \n ",getpid());
	
	pid = fork();

//---- ejemplo de switch ---------------------------	
    switch (pid ) {
           
    case -1:
        printf ("Error. No se crea proceso hijo");
        return -1;
        break ;

    case 0:
        printf("switch: Soy el hijo: %d, mi papa es: %d, fork() devolvio %d\n", getpid(),getppid(),pid);
	   	break ;

    default:
        printf("switch: Soy el padre: %d, mi papa es: %d, fork() devolvio %d\n", getpid(),getppid(),pid);
        break ;
   }    

//----fin ejemplo de switch ---------------------------	

//acá llegan todos los procesos

//---- ejemplo de if ----------------------------------	

	if (pid==0) { 	//hijo	
		printf("if: Soy el hijo: %d, mi papa es: %d, fork() devolvio %d\n", getpid(),getppid(),pid);

	}else {
		printf("if: Soy el padre: %d, mi papa es: %d, fork() devolvio %d\n", getpid(),getppid(),pid);
	}

//---- fin ejemplo de if ----------------------------------	

//acá llegan todos los procesos


	exit(0);
}



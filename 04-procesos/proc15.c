/*
 * Ejercicio 15 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main(void) {
	
	int err;
	
	err = execl	("/bin/ls", "ls", "-l", (char *)NULL);
	//err = execl("/otro_directorio/ls", "ls", "-l", (char *)NULL);
	
	if (err == -1)
		printf("Este printf se ejecuta en caso de error. Por que?\n");
			
	exit(0);

}





	

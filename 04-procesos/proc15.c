/*
 * Ejercicio 15 de la guía práctica Procesos
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <wait.h>

int main(void) {
	
	int err;
	
	err = execl	("/bin/ls", "ls", "-l", (char *)NULL);
	//err = execl("/otro_directorio/ls", "ls", "-l", (char *)NULL);
	
	if (err == -1)
		printf("Este printf se ejecuta en caso de error. Por que?\n");
			
	return (0);

}





	

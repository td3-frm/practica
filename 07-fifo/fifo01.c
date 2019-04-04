/*
 * Ejercicio 1 del TP FIFO
 * Tipica implementacion de una FIFO.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MENSAJE "HOLA PROCESO HIJO"
#define FIFO_PATH "/tmp/MI_FIFO"

main(){

	int err, fifo_d;
	char buff[80];
	int leido;

	unlink(FIFO_PATH);    //si la FIFO existe la borro                   

	// FIFO puede ser leida, escrita y ejecutada por: 
	err = mkfifo(FIFO_PATH, S_IRUSR|S_IWUSR|S_IXUSR|  // el usuario que la creo.
	                        S_IRGRP|S_IWGRP|S_IXGRP|  // el grupo al que pertenece el usuario.
	                        S_IROTH|S_IWOTH|S_IXOTH); // el resto de los usuarios del sistema.

	//err = mkfifo(FIFO_PATH, 0777);
	if(err == -1) {
		write (0, "\nError al crear FIFO, la FIFO ya existe", sizeof("\nError al crear FIFO, la FIFO ya existe")); 
	}else {
		write (0, "\nFIFO creado correctamente\n", sizeof("\nFIFO creado correctamente\n")); 
	}

	switch (fork()){ 
		
		case -1:	//ERROR	
			write (0, "\nError al crear hijo", sizeof("\nError al crear hijo")); 
			return -1;
		break;			

		case 0:		//Hijo
			write (0, "\nEntrando proceso HIJO", sizeof("\nEntrando proceso HIJO")); 

			sleep(5);

			fifo_d = open(FIFO_PATH, O_RDONLY, 0); // O_NONBLOCK
			if(fifo_d == -1){
				write (0, "\nHIJO: Error al abrir FIFO ", sizeof("\nHIJO: Error al abrir FIFO "));
				return -1;
			}else {
				write (0, "\nHIJO: FIFO abierto correctamente", sizeof("\nHIJO: FIFO abierto correctamente"));
			}
			
			// Se lee FIFO
			leido = read(fifo_d, buff, sizeof(buff));	
			if(leido == -1){
				write (0, "\nHIJO: Error al leer en FIFO", sizeof("\nHIJO: Error al leer en FIFO"));
			}else {
				write (0, "\nHIJO: Leido del FIFO: ", sizeof("\nHIJO: Leido del FIFO: "));
				write (0, buff, leido-1); 
				write (0, "\n", sizeof("\n")); 
			}
			close(fifo_d); 

			write (0, "\nSaliendo proceso HIJO\n", sizeof("\nSaliendo proceso HIJO\n")); 
			exit(0);	

		break;
		
		default:     //Padre
			write (0, "\nEntrando proceso PADRE", sizeof("\nEntrando proceso PADRE")); 
		
			sleep(2);

			fifo_d = open(FIFO_PATH, O_WRONLY, 0);
			if(fifo_d == -1){
				write (0, "\nPADRE: Error al abrir FIFO ", sizeof("\nPADRE: Error al abrir FIFO "));
				return -1;
			}else {
				write (0, "\nPADRE: FIFO abierto correctamente", sizeof("\nPADRE: FIFO abierto correctamente"));
			}

			// Se escribe en el FIFO
			err = write(fifo_d, MENSAJE, sizeof(MENSAJE));
			if(err == -1) {
				write (0, "\nPADRE: Error al escribir en FIFO", sizeof("\nPADRE: Error al escribir en FIFO"));
			} else {
				write (0, "\nPADRE: Escritos MENSAJE en FIFO", sizeof("\nPADRE: Escritos MENSAJE en FIFO"));
			}
			
			close(fifo_d);
			
			wait(NULL);	

			write (0, "\nSaliendo proceso PADRE\n", sizeof("\nSaliendo proceso PADRE\n")); 
					
		break;	
	}
	
	//Eliminación FIFO
	//if (unlink(FIFO_PATH) < 0){
	//	printf("\nNo se puede borrar FIFO.\n"); }
		
	exit(0);

}

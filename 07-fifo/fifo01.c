/*
 * Ejercicio 1 de la guía práctica FIFO
 * Tipica implementacion de una memoria FIFO.
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
			
	// FIFO puede ser leida, escrita y ejecutada por: 
	err = mkfifo(FIFO_PATH, S_IRUSR|S_IWUSR|S_IXUSR|  // el usuario que la creo.
	                        S_IRGRP|S_IWGRP|S_IXGRP|  // el grupo al que pertenece el usuario.
	                        S_IROTH|S_IWOTH|S_IXOTH); // el resto de los usuarios del sistema.
	if(err == -1)
		printf("Error al crear FIFO (%d)\n", err);
	else 
		printf("FIFO creado correctamente (%d)\n", err);
	
	switch (fork()){ 
		
		case 0:
			printf("Entrando proceso HIJO\n"); 
			fifo_d = open(FIFO_PATH, O_RDONLY, 0); // O_NONBLOCK 
			if(err == -1){
				printf("HIJO : Error al abrir FIFO (%d). %s \n", err, strerror(errno) );  } 
			else {
				printf("HIJO : FIFO abierto correctamente (%d)\n", err);}
			
			// Se lee FIFO
			leido = read(fifo_d, buff, sizeof(buff));	
			if(leido == -1){
				printf("HIJO : Error al leer en FIFO (%d). %s \n", err, strerror(errno)); }
			else {
				write (0, "HIJO : Leido del FIFO '", sizeof("HIJO : Leido del FIFO '"));
				write (0, buff, leido-1); 
				write (0, "'\n", sizeof("'\n")); }

			close(fifo_d); 
 			printf("Saliendo proceso HIJO\n"); 	
			exit(0);	
		break;	
		
		case -1:		
			printf("Error al crear hijo\n");
			return -1;
		break;			
		
		default:
			printf("Entrando proceso PADRE\n");
			fifo_d = open(FIFO_PATH, O_WRONLY, 0); 
			if(err == -1)
				printf("PADRE: Error al abrir FIFO (%d). %s \n", err, strerror(errno) ); 
			else 
				printf("PADRE: FIFO abierto correctamente (%d)\n", err);

			// Se escribe en el FIFO
			err = write(fifo_d, MENSAJE, sizeof(MENSAJE));
			if(err == -1)
				printf("PADRE: Error al escribir en FIFO (%d). %s \n", err, strerror(errno));
			else 
				printf("PADRE: Escritos %d bytes en FIFO\n", err);
			
			close(fifo_d); 
			
			printf("Saliendo proceso PADRE\n"); 					
			wait(NULL);	
					
		break;	
	}
	
	// if (unlink(FIFO_PATH) < 0)
		// printf("No se puede borrar FIFO.\n");			
	return 0;	

}

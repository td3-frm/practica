/*
 * Ejercicio 2 de la guía práctica FIFO
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MENSAJE "HOLA PROCESO HIJO"
#define FIFO_PATH "/tmp/MI_FIFO"

main(){

	int err, file_d;
	char buff[80];
	int leido;
			
	// FIFO puede ser leida, escrita y ejecutada por: 
	err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.
	if(err == -1)
		printf("Error al crear FIFO (%d)\n", err);
	else 
		printf("FIFO creado correctamente (%d)\n", err);
		
	switch (fork()){ 
		
		case 0:
			printf("Entrando proceso HIJO\n"); 
			file_d = open(FIFO_PATH, O_RDONLY, 0); // O_NONBLOCK 
			if(err == -1){
				printf("HIJO : Error al abrir FIFO (%d)\n", err); }
			else {
				printf("HIJO : FIFO abierto correctamente (%d)\n", err);}
			
			// Se lee FIFO
			leido = read(file_d, buff, sizeof(buff));	
			if(leido == -1){
				printf("HIJO : Error al leer FIFO (%d)\n", leido); }
			else {
				write (0, "HIJO : Leido del FIFO '", sizeof("HIJO : Leido del FIFO '"));
				write (0, buff, leido-1); 
				write (0, "'\n", sizeof("'\n")); }

			close(file_d); 
 			printf("Saliendo proceso HIJO\n"); 	
			exit(0);	
		break;	
		
		case -1:		
			printf("Error al crear hijo\n");
			return -1;
		break;			
		
		default:
			printf("Entrando proceso PADRE\n");
			//~ file_d = open(FIFO_PATH, O_WRONLY, 0); 
			//~ if(err == -1)
				//~ printf("PADRE: Error al abrir FIFO (%d)\n", err);
			//~ else 
				//~ printf("PADRE: FIFO abierto correctamente (%d)\n", err);
//~ 
			//~ // Se escribe en el FIFO
			//~ err = write(file_d, MENSAJE, sizeof(MENSAJE));
			//~ if(err == -1)
				//~ printf("PADRE: Error al escribir en FIFO (%d)\n", err);
			//~ else 
				//~ printf("PADRE: Escritos %d bytes en FIFO\n", err);
			//~ 
			//~ close(file_d); 
			//~ 
			printf("Saliendo proceso PADRE\n"); 					
			wait(NULL);	
					
		break;	
	}
	
	//~ if (unlink(FIFO_PATH) < 0)
 		//~ printf("No se puede borrar FIFO.\n");			
	return 0;	

}

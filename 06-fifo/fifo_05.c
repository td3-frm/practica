/*
 * Ejercicio 5 del TP FIFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<sys/wait.h> 

#define MENSAJE "HOLA PROCESO PADRE"
#define FIFO_PATH "/tmp/MI_FIFO"

int main(){

   int err, fifo_d;
   char buff[80];
   int leido;

   unlink(FIFO_PATH);    //si la FIFO existe la borro                   

   // FIFO puede ser leida, escrita y ejecutada por: 
   err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.
   

   switch (fork()){ 
      
      case -1:
         write(STDOUT_FILENO, "Error al crear hijo\n", sizeof("Error al crear hijo\n"));
         return -1;
      break;

      case 0:

        sleep(2);

		fifo_d = open(FIFO_PATH, O_WRONLY, 0);
		if(fifo_d == -1){
			write(STDOUT_FILENO, "Error al abrir FIFO\n", sizeof("Error al abrir FIFO\n"));
		return -1;         }

		err = write(fifo_d, MENSAJE, sizeof(MENSAJE));
		if(err == -1) {
			write(STDOUT_FILENO, "Error al escribir en FIFO\n", sizeof("Error al escribir en FIFO\n"));
		}
         
         close(fifo_d);

        sleep(3);
		write (0, "Hijo termina\n", sizeof("Hijo termina\n")); 
        exit(0);
      break;

      default:
      
        sleep(3);

        /*  
			El Padre que debe hacer con la FIFO ?
        */      
         


        wait(NULL);   

        write (0, "Padre termina\n", sizeof("Padre termina\n")); 

      break;   
   }
   
   exit(0);

}

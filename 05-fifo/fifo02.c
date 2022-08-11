/*
 * Ejercicio 2 del TP FIFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include<sys/wait.h> 

#define MENSAJE "HOLA PROCESO HIJO"
#define FIFO_PATH "/tmp/MI_FIFO"

int main(){

   int err, fifo_d;
   char buff[80];
   int leido;
   
   unlink(FIFO_PATH);    //si la FIFO existe la borro                   

   // FIFO puede ser leida, escrita y ejecutada por: 
   err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.
   
   if(err == -1) {
      write (STDOUT_FILENO, "Error al crear FIFO, la FIFO ya existe\n", sizeof("Error al crear FIFO, la FIFO ya existe\n"));
   }else {
      write (STDOUT_FILENO, "FIFO creada correctamente\n", sizeof("FIFO creada correctamente\n"));
   }

   switch (fork()){

      case -1:
         write(STDOUT_FILENO, "Error al crear hijo\n", sizeof("Error al crear hijo"\n));
         return -1;
      break;

      case 0:

         write (STDOUT_FILENO, "Hijo inicia\n", sizeof("Hijo inicia\n"));

         sleep(5);

         fifo_d = open(FIFO_PATH, O_RDONLY, 0); 
         
         if(fifo_d == -1){
            write (STDOUT_FILENO, "Hijo, error al abrir FIFO\n", sizeof("Hijo: error al abrir FIFO\n"));
            return -1;
         }else {
            write (STDOUT_FILENO, "Hijo, FIFO abierta correctamente\n", sizeof("Hijo: FIFO abierta correctamente\n"));
         }

         // Se lee FIFO
         leido = read(fifo_d, buff, sizeof(buff));
         if(leido == -1){
            write(STDOUT_FILENO, "Hijo, error al leer FIFO\n", sizeof("Hijo: error al leer FIFO\n"));
         }else {
            write(STDOUT_FILENO, "Hijo, leido de la FIFO \"", sizeof("Hijo: leido de la FIFO \""));
            write(STDOUT_FILENO, buff, leido-1);
            write(STDOUT_FILENO, "\"\n", sizeof("\"\n"));
         }
         close(fifo_d);

         write (0, "Hijo termina\n", sizeof("Hijo termina\n")); 
         exit(0);
      break;

      default:
         write (STDOUT_FILENO, "Padre inicia\n", sizeof("Padre inicia\n"));

         /*  
             El padre, ¿que debe hacer con la FIFO?
         */      
         
         wait(NULL);   
         
         write (0, "Padre termina\n", sizeof("Padre termina\n")); 
         
         break;
   }
   
   // Eliminación FIFO
   // if (unlink(FIFO_PATH) == 0)
   // {
   // 	printf("Se borra FIFO\n"); 
   // }
   // else
   // {
   // 	printf("No se puede borrar FIFO\n"); 
   // } 
       
   exit(0);   
}

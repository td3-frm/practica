/*  
 * Ejercicio de la guía práctica Memoria compartida
 * 
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/shm.h>


#define MEM_COM "MEM_COMP_3"

int main()   {   

int fd, ft, leido, largo, i,error;
int contador;
int *ptr;
char buff[1024];
struct stat sb;
char nroascii ;

//--- Crea la memoria compartida, y obtiene el descriptor
   fd = shm_open(MEM_COM , O_RDWR|O_CREAT, 0777 );
   if (fd == -1){
       printf("Error en shm_open, %d,\n", fd);
       exit(-1); }
   
   write (STDOUT_FILENO, "\nMemoria compartida creada", sizeof("\nMemoria compartida creada"));

//--- ----
   largo = 0;   
   error = ftruncate(fd, largo);
   if (error == -1){
       printf("Error en ftruncate\n", error);
       exit(-1); }

//--- Se dimensiona la memoria y se pone a cero
   largo = 1024;   
   error = ftruncate(fd, largo);
   if (error == -1){
       printf("Error en ftruncate\n", error);
       exit(-1); }

   write (STDOUT_FILENO, "\nMemoria compartida dimensionada", sizeof("\nMemoria compartida dimensionada"));

//--- Se mapea la memoria compartida al espacio de memoria del proceso
 //    Devuelve un puntero al área reservada
   ptr = mmap(NULL, 10, PROT_READ |PROT_WRITE, MAP_SHARED, fd, 0 );
   if (ptr == (void *)-1){
       printf("Error en mmap\n", ptr);
       exit(-1); }

   write (STDOUT_FILENO, "\nEscribiendo en memoria\n", sizeof("\nEscribiendo en memoria\n"));

    contador = 0x30; // Se inicializa en 0 ASCII
    for(i=0;i<10;i++)     {
         nroascii = contador;            
         contador = contador+1;
         memcpy((ptr+ i), &nroascii, sizeof(nroascii));
         sleep(1);
   }

//-- Determine the size of the shared memory
    error = fstat(fd, &sb);
    if (error == -1){
       printf("Error en fstat\n", error);
       exit(-1); }
          
      
//-- Se lee de la memoria compartida y se imprime por pantalla
    write (STDOUT_FILENO, "\nLeido de memoria: ", sizeof("\nLeido de memoria: "));
    write(STDOUT_FILENO, ptr, sb.st_size);

    sleep(1);

    exit(0); 
}

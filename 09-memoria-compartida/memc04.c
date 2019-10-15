/*  
 * Ejercicio 3 del TP Memoria compartida
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

#define MEM_COM "MEM_COM"
#define MENSAJE "INFORMACION PARA OTRO PROCESO\n"

int main()  {   

int fd, error, leido, largo, pid ;
int *ptr;
char buff[1024];
struct stat sb;


//--- Crea la memoria compartida, y obtiene el descriptor
   fd = shm_open(MEM_COM , O_RDWR|O_CREAT, 0777 );
   if (fd == -1){
          printf("\nError en shm_open\n");
          exit(-1); }


   pid = fork();

   if (pid == 0) {   

    //--- Se mapea la memoria compartida al espacio de memoria del proceso
    //    Devuelve un puntero al área reservada
      ptr = mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
      if (ptr == (void *)-1){
             printf("\nError en mmap\n");
             exit(-1); }
   
       printf ("Proceso hijo, direccion del puntero %p\n", ptr);   

       //--- Copia Mensaje en la memoria
       memcpy(ptr, MENSAJE, sizeof(MENSAJE));
   
       printf ("MENSAJE copiado en memoria\n");   

       exit(0);

   }
   
   if (pid > 0) {   

    //--- Se mapea la memoria compartida al espacio de memoria del proceso
    //    Devuelve un puntero al área reservada
      ptr = mmap(NULL, 10, PROT_READ |PROT_WRITE, MAP_SHARED, fd, 0 );
      if (ptr == (void *)-1){
          printf("\nError en mmap\n");
          exit(-1); }

      printf ("Proceso padre, direccion del puntero %p\n", ptr);   
   
      wait(NULL);

//-- Lee de la memoria compartida y se imprime por pantalla
//   largo=write(STDOUT_FILENO, ptr, sb.st_size);

//-- Copia de la memoria compartida en buff
        memcpy(buff, ptr, sb.st_size);
        printf("\nLeido: %s", buff);

//--- Borrar memoria compartida   
       error = shm_unlink(MEM_COM);
       if (error == -1){
          printf("\nError en shm_unlink\n");
          exit(-1); }
   }

       exit(0);

}

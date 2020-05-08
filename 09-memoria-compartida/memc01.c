/*  
 * Ejercicio 1 del TP Memoria compartida
 * Tipica implementacion de una memoria compartida
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

#define MEM_COM "MEM_COM"  //nombre
#define MENSAJE "INFORMACION PARA OTRO PROCESO\n"

int main()  {   

int fd, error, leido, largo ;
int *ptr;
char buff[1024];
struct stat sb;

printf("O_RDWR : %d\n", O_RDWR);
printf("O_WRONLY : %d\n", O_WRONLY);
printf("O_RDWR : %d\n", O_RDWR);
printf("O_RDWR : %d\n", O_RDWR);
printf("O_RDWR : %d\n", O_RDWR);
printf("O_RDWR : %d\n", O_RDWR);
printf("O_RDWR : %d\n", O_RDWR);
printf("O_RDWR : %d\n", O_RDWR);

|       O_RDONLY
              Open the queue to receive messages only.

       
              Open the queue to send messages only.

        Open the queue to both send and receive messages.

       Zero or more of the following flags can additionally be ORed in oflag:

       O_CLOEXEC (since Linux 2.6.26)
              Set the close-on-exec flag for the message queue descriptor.  See open(2) for a discussion of why this flag is useful.

       O_CREAT
              Create the message queue if it does not exist.  The owner (user ID) of the message queue is set to the effective user ID of the calling
              process.  The group ownership (group ID) is set to the effective group ID of the calling process.

       O_EXCL If O_CREAT was specified in oflag, and a queue with the given name already exists, then fail with the error EEXIST.

       O_NONBLOCK


//--- Crea la memoria compartida, y obtiene el descriptor
   fd = shm_open(MEM_COM , O_RDWR|O_CREAT, 0777 );
   if (fd == -1){
       printf("\nError en shm_open\n");
       exit(-1); }

//--- Se dimensiona la memoria y se pone a cero
   largo = 1024;   
   error = ftruncate(fd, largo);
   if (error == -1){
       printf("\nError en ftruncate\n");
       exit(-1); }


 //--- Se mapea la memoria compartida al espacio de memoria del proceso
 //    Devuelve un puntero al área reservada
   ptr = mmap(NULL, 10, PROT_READ |PROT_WRITE, MAP_SHARED, fd, 0 );
   if (ptr == (void *)-1){
       printf("\nError en mmap\n");
       exit(-1); }

    printf ("Direccion de memoria local donde arranca la memoria %p\n", ptr);   

    printf ("Hacer >$ls /dev/shm \n");
   
    sleep(10);
    
    //--- Copia Mensaje en la memoria
    memcpy(ptr, MENSAJE, sizeof(MENSAJE));

    printf ("MENSAJE copiado en memoria\n");   

    printf ("Hacer >$cat /dev/shm/MEM_COM\n");
    
    sleep(10);

//--- Lee el estado de la memoria y se guarda en la estructura sb
//     el tamaño del archivo es el campo st_size
	error = fstat(fd, &sb);
	if (error == -1){
       printf("\nError en fstat\n");
       exit(-1); }
       
//-- Copia  de la memoria compartida en buff
	memcpy(buff, ptr, sb.st_size);
	printf("\nLeido de memoria compartida: %s", buff);    


///////////// vuelve a leer ////////////////////////////////
//--- Lee el estado de la memoria y se guarda en la estructura sb
//     el tamaño del archivo es el campo st_size
	error = fstat(fd, &sb);
	if (error == -1){
       printf("\nError en fstat\n");
       exit(-1); }


//-- Lee de la memoria compartida y se imprime por pantalla
	write (0,"\nLeido por segunda vez de la memoria: ",sizeof("\nLeido por segunda vez de la memoria: "));
    largo=write(STDOUT_FILENO, ptr, sb.st_size);


/*
//--- Borrar memoria compartida   
    error = shm_unlink(MEM_COM);
    if (error == -1){
       printf("\nError en shm_unlink\n");
       exit(-1); }
	
	printf("\nObjeto de memoria borrado\n");

 */
 
    exit(0);
}

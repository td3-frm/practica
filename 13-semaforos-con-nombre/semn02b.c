#include <string.h>
#include <stdio.h>
#include <pthread.h>    
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>   
#include <errno.h>
#include <sys/mman.h>
#include <sys/shm.h>

int t, total, contador, s, longitud;
#define MEM_COM "MEM_COM"  //nombre

int main()	{
int fd, error, leido, largo ;
int *ptr;
char buff[1024];
struct stat sb;

//--- Crea la memoria compartida, y obtiene el descriptor
	fd = shm_open(MEM_COM , O_RDWR, 0777 );
	if (fd == -1){
		printf("Error en shm_open, %d,\n", fd);
		exit(-1); }

	printf("Objeto de memoria abierto\n");

//--- Se mapea la memoria compartida al espacio de memoria del proceso
//    Devuelve un puntero al área reservada
	ptr = mmap(NULL, 10, PROT_READ |PROT_WRITE, MAP_SHARED, fd, 0 );
	if (ptr == (void *)-1){
		printf("Error en mmap %p\n", ptr);
		exit(-1); }

	printf("Memoria mapeada\n");

		
//--- Lee el estado de la memoria y se guarda en la estructura sb
//     el tamaño del archivo es el campo st_size
		error = fstat(fd, &sb);
		if (error == -1){
			printf("Error en fstat %d \n", error);
			exit(-1); }

//-- Lee de la memoria compartida y se imprime por pantalla
		write (STDOUT_FILENO, "\nLeido de memoria: ", sizeof("\nLeido de memoria: "));
		largo=write(STDOUT_FILENO, ptr, sb.st_size);
		write (STDOUT_FILENO, "\n", sizeof("\n"));
        			
	exit(0);

}


#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>   
#include <errno.h>
#include <sys/mman.h>
#include <sys/shm.h>

int i, total, contador, s;
#define MEM_COM "MEM_COM"  //nombre

int main()	{
int fd, error, leido, largo ;
int *ptr;
char buff[1024];
struct stat sb;
char nroascii ;

//--- Borrar memoria compartida por si ya existe  
	error = shm_unlink(MEM_COM);
	if (error == -1){
		printf("El objeto de memoria no existe\n"); }

//--- Crea la memoria compartida, y obtiene el descriptor
	fd = shm_open(MEM_COM , O_RDWR|O_CREAT, 0777 );
	if (fd == -1){
		printf("Error en shm_open, %d,\n", fd);
		exit(-1); }

	printf("Objeto de memoria creado\n");

//--- Se dimensiona la memoria y se pone a cero
	largo = 1024;   
	error = ftruncate(fd, largo);
	if (error == -1){
		printf("Error en ftruncate %d\n", error);
		exit(-1); }

 //--- Se mapea la memoria compartida al espacio de memoria del proceso
 //    Devuelve un puntero al área reservada
	ptr = mmap(NULL, 10, PROT_READ |PROT_WRITE, MAP_SHARED, fd, 0 );
	if (ptr == (void *)-1){
		printf("Error en mmap %p\n", ptr);
		exit(-1); }

	printf("Memoria mapeada en: %p\n", ptr);

	contador = 0x41; // Se inicializa en 0 ASCII
	for(i = 0 ; i < 26 ; i++)     {
		nroascii = contador;            
		contador = contador+1;
		memcpy((ptr+ i), &nroascii, sizeof(nroascii));
	    sleep(1);
	}
	
	printf("Fin escritura\n");

	exit(0);	
}


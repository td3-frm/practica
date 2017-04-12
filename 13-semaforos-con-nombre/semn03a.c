/* Ejercicio 3 programa 1 del TP de semaforos con nombre */

/*------- Productor ------------*/

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

#define MAX_BUFFER          10	// Buffer
#define DATOS_A_PRODUCIR    30

#define MEM_COM "MEM_COM"
#define sema_dato "/sem_dato"
#define sema_lugar "/sem_lugar"

sem_t *sem_dato, *sem_lugar;   // Semaforos
int *ptr;
struct stat sb;
int fd, error, leido, largo ;
int dato, i, pos, s, contador;

//-------------------------------------------------------

int main() {

//--- Borrar memoria compartida por si ya existe  
	error = shm_unlink(MEM_COM);
	if (error == -1){
		printf("El objeto de memoria no existe\n"); }

//------Se elimina semaforo por si ya existe
	s=sem_unlink(sema_lugar);
	if (s == -1){
		printf("El semaforo no existe\n"); }

	s=sem_unlink(sema_dato);
	if (s == -1){
		printf("El semaforo no existe\n"); }

	printf("Se crean semaforos\n");


//------ crea el sem_lugar
	sem_lugar = sem_open(sema_lugar, O_CREAT , 0666, MAX_BUFFER);
	if (sem_lugar == SEM_FAILED) {
		printf("ERROR sem_open()\n");
		exit(-1);     }

//------ crea el sem_dato
	sem_dato = sem_open(sema_dato, O_CREAT , 0666, 0);
	if (sem_lugar == SEM_FAILED) {
		printf("ERROR sem_open()\n");
		exit(-1);     }

	printf("Semaforos creados\n");


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
		printf("Error en ftruncate\n", error);
		exit(-1); }

 //--- Se mapea la memoria compartida al espacio de memoria del proceso
 //    Devuelve un puntero al area reservada
	ptr = mmap(NULL, 10, PROT_READ |PROT_WRITE, MAP_SHARED, fd, 0 );
	if (ptr == (void *)-1){
		printf("Error en mmap %p\n", ptr);
		exit(-1); }

	printf("Memoria mapeada en: %p\n", ptr);

//---------------- PRODUCTOR ---------------------------
	pos = 0;
	contador = 1000; 

	for(i=0; i < DATOS_A_PRODUCIR; i++ ) {

		s = sem_wait(sem_lugar);            // Decrementa sem_lugar o esperar si igual a 0
		if (s != 0) {
			printf("ERROR; sem_wait() = %d\n", s);
			exit(-1);	      }

	    sleep(1);

		memcpy((ptr+ pos), &contador, sizeof(contador));

		pos = pos + 1;
		if (pos >= MAX_BUFFER) {
			pos=0;   }

		s=sem_post(sem_dato);      // Incrementa sem_dato   
		if (s != 0) {
	      printf("ERROR sem_post()\n");
	      exit(-1);     }

		printf("Productor dato: %d \n", contador);

		contador = contador + 1 ;

	}
   
	printf("Termina Productor: %d\n",i);
   
	exit(0);
}

//------------------------------------------------------------//


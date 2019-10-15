/* Ejercicio 3 programa 2 del TP de semaforos con nombre */

/*------- Consumidor ------------*/


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
#define DATOS_A_CONSUMIR    30

#define MEM_COM "MEM_COM"
#define sema_dato "/sem_dato"
#define sema_lugar "/sem_lugar"

sem_t *sem_dato, *sem_lugar;   // Semaforos
int *ptr;
struct stat sb;
int fd, error;


//-------------------------------------------------------

int main() {

int dato, i, pos, s;

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

 //--- Se mapea la memoria compartida al espacio de memoria del proceso
 //    Devuelve un puntero al area reservada
	ptr = mmap(NULL, 10, PROT_READ |PROT_WRITE, MAP_SHARED, fd, 0 );
	if (ptr == (void *)-1){
		printf("Error en mmap %p\n", ptr);
		exit(-1); }

	printf("Memoria mapeada en: %p\n", ptr);


//---------------- CONSUMIDOR ---------------------------

	pos=0;
    
	for(i=0; i < DATOS_A_CONSUMIR; i++ ) {
		s=sem_wait(sem_dato);            // Decrementa sem_dato o esperar si igual a 0
		if (s != 0) {
			printf("ERROR; sem_wait() = %d\n", s);
			exit(-1);      }
       
		sleep(1);

		memcpy(&dato, (ptr + pos), sizeof(dato));

		pos = pos + 1;
		if (pos>= MAX_BUFFER) {
			pos=0;   }
      
		s=sem_post(sem_lugar);   // Incrementa sem_lugar   
		if (s != 0) {
		 	printf("ERROR sem_post()\n");
	      	exit(-1);     }

		printf("Consumidor dato: %d \n", dato);
     
	}
  
	printf("Termina Consumidor: %d\n",i);

	exit(0);
   
}

//------------------------------------------------------------//


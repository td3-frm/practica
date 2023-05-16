/* Ejercicio 4 del TP de semaforos sin nombre */

/* productor-consumidor con semaforos */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUFFER          10	// Buffer
#define DATOS_A_PRODUCIR    20  // DATOS A PRODUCIR POR CADA PRODUCTOR

static int buffer[MAX_BUFFER] = {0};   // Buffer comun

pthread_t th1, th2;      	// Hilos
sem_t sem_dato,sem_lugar;   // Semaforos


//---------------- PRODUCTOR ---------------------------

void Productor(void) {
int dato, i, pos, s;

	pos = 0;
	dato = 1000;                     // Producir dato
	
	for(i=0; i < DATOS_A_PRODUCIR; i++ ) {
		
		sleep(1);
		
		dato++;
		buffer[pos] = dato;      
		pos = (pos + 1);
		
		if (pos >= MAX_BUFFER) {
			pos=0;   }
		
		printf("Productor dato: %d \n", dato);
	}
	
	printf("Termina Productor: %d\n",i);
	pthread_exit(0);

}

//---------------- CONSUMIDOR ---------------------------
void Consumidor(void){    
int dato, i, pos, s;

	pos=0;
    
	for(i=0; i < DATOS_A_PRODUCIR; i++ ) {

		sleep(1);

		dato = buffer[pos];
		pos = (pos + 1) ;
		if (pos>= MAX_BUFFER) {
			pos=0;   }
      
		printf("Consumidor dato: %d \n", dato);
     
	}
  
	printf("Termina Consumidor: %d\n",i);
	pthread_exit(0);
}

//-------------------------------------------------------

int main() {

int s;

	printf("Se crean semaforos\n");

//------ Crear semaforos 


//------ Crear hilos 

	printf("Se crean hilos\n");

	pthread_create(&th1, NULL, (void *)&Productor, NULL);
	pthread_create(&th2, NULL, (void *)&Consumidor, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th2, NULL);

	printf("Termina main() \n");
   
	pthread_exit(0);
}

//------------------------------------------------------------//


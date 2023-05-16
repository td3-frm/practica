/* Ejercicio 3 del TP de semaforos sin nombre */

#include <stdio.h>
#include <pthread.h>    
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

//------- variables globales

pthread_t hilo[2];
sem_t sem;
int t[2];


//---------------- Hilo INCR ---------------------------//
void *INCR(void *nro){

int numero,s,sval,i;

	numero= *(int*)nro;
	printf ("Soy el hilo %lx voy a incrementar semaforo %d veces\n", pthread_self(),numero);

//------ Se incrementa sem
	for(i=0; i < numero ; i++){
		s=sem_post(&sem);
		if (s!= 0) {
			printf("ERROR sem_post()\n");
			exit(-1);     }
		printf("Sem_post OK\n");
	}
	
	sleep(1);
	
	pthread_exit (NULL);
}

//---------------- Hilo DECR ---------------------------//
void *DECR(void *nro){

int numero,s,sval,i;

	numero= *(int*)nro;
	printf ("Soy el hilo %lx voy a decrementar semaforo %d veces\n", pthread_self(),numero);

//------ Se decrementa sem
	for(i=0; i < numero ; i++){
		s = sem_wait(&sem);
		if (s!= 0) {
			printf("ERROR sem_wait()\n");
			exit(-1);     }
		printf("Sem_wait OK\n");
	}
	
	sleep(1);
	
	pthread_exit (NULL);

}

//-----------------------------------------------------------//

int main() {

int s,sval,rc;
 
	printf ("Main crea el semaforo\n");

//------ inicializa el sem sin nombre 
	s=sem_init(&sem, 0, 0);
	if (s != 0) {
		printf("ERROR sem_init()\n");
		exit(-1);     }

//------lee valor de sem 

	sem_getvalue(&sem, &sval);
	printf("Valor inicial de semaforo: %d\n",sval);


//------ Crea los hilos

	t[0]=5;
	rc = pthread_create (&hilo[0], NULL, INCR, (void *)&t[0]);
	if (rc)    {
		printf ("ERROR; pthread_create() = %d\n", rc);
		exit (-1);    }
	
	t[1]=6;
	rc = pthread_create (&hilo[1], NULL, DECR, (void *)&t[1]);
	if (rc)    {
		printf ("ERROR; pthread_create() = %d\n", rc);
		exit (-1);    }
	
	printf ("El main crea hilos: %lx, %lx \n", hilo[0], hilo[1]);

//-------- Espera fin de hilos
	pthread_join (hilo[0], NULL);
	pthread_join (hilo[1], NULL);


//------lee valor de sem
	sem_getvalue(&sem, &sval);
	printf("Valor final del semaforo: %d\n",sval);


//------elimina sem
	s=sem_destroy(&sem);
	if (s != 0) {
		printf("ERROR sem_unlink()\n");
		exit(-1);  }

	printf("Fin del main() \n");
	
	pthread_exit (NULL);

}



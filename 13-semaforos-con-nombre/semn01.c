//---------------- Uso de semáforos sin nombre ----------------//

#include <stdio.h>
#include <pthread.h>    
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

//------- variables globales

pthread_t hilo;
sem_t *sem;
#define semaforo "/sema1"


//---------------- Hilo ---------------------------//

void *Post_Sem(){
int s;

	printf ("Soy el hilo voy a incrementar semaforo\n");
 
	sleep(3);

//------ Se incrementa el semáforo
	s=sem_post(sem);
	if (s != 0) {
      printf("ERROR sem_post()\n");
      exit(-1);     }

	pthread_exit (NULL);

}

//-----------------------------------------------------------//

int main() {

  int s,sval,rc;
 
  printf ("Main crea el semaforo\n");
  
//------ crea el semáforo 
	sem = sem_open(semaforo, O_CREAT , 0666, 0);
	if (sem == SEM_FAILED) {
		printf("ERROR sem_open()\n");
		exit(-1);     }

//------lee valor de semáforo 
	sem_getvalue(sem, &sval);
	printf("Valor de semaforo: %d\n",sval);


//------ Creación de hilo 
	rc = pthread_create (&hilo, NULL, Post_Sem, NULL);
 	if (rc)    {
    	printf ("ERROR; pthread_create() = %d\n", rc);
		exit (-1);    }

//------decremento de semáforo 
	s = sem_wait(sem);
	if (s != 0) {
		printf("ERROR sem_wait()\n");
		exit(-1);     }

//------Se cierra semáforo
   s=sem_close(sem);
   if (s != 0) {
      printf("ERROR sem_close()\n");
      exit(-1);  }

//------Se elimina semáforo
   s=sem_unlink(semaforo);
   if (s != 0) {
      printf("ERROR sem_unlink()\n");
      exit(-1);  }

//--------------------------------------------
   
	pthread_join (hilo, NULL);
  
	printf("Fin del main() \n");

	pthread_exit (NULL);

}



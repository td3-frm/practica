#include <stdio.h>
#include <pthread.h>    
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

//---uso de semaforos con nombre
//--espera de semaforo 

pthread_t hilo[2];
sem_t *sem;

//---------------- Hilo ---------------------------//
void * func_sem(){

  int s,sval;

//   sleep(5);

  printf ("Soy el hilo %lx voy a incrementar semaforo\n", pthread_self());
 
//------ Se incrementa el semaforo -------------

   sleep(1);
   
   s=sem_post(sem);
   
   if (s<0) {
      printf("ERROR sem_post()\n");
      exit(-1);     }

//------Se lee valor de semaforo -------------

   sem_getvalue(sem, &sval);
   printf("sem_post: %d\n",sval);

   pthread_exit (NULL);

}

//-----------------------------------------------------------//

int main() {

  int s,sval,rc;
  
//------ Se crea semaforo con valor 0 -------------

   sem = sem_open("/sema1", O_CREAT , 0666, 0);
   if (sem == SEM_FAILED) {
      printf("ERROR sem_open()\n");
      exit(-1);     }

//------Se lee valor de semaforo -------------

   sem_getvalue(sem, &sval);

   printf("Valor de semaforo: %d\n",sval);

//------ Se crean hilos -------------

 rc = pthread_create (&hilo[0], NULL, func_sem, NULL);
 if (rc)    {
      printf ("ERROR; pthread_create() = %d\n", rc);
      exit (-1);    }
      
rc = pthread_create (&hilo[1], NULL, func_sem, NULL);
 if (rc)    {
      printf ("ERROR; pthread_create() = %d\n", rc);
      exit (-1);    }


 printf ("El main crea hilos: %lx, %lx \n", hilo[0], hilo[1]);

//------Se decrementa semaforo -------------

  s = sem_wait(sem);
   
  if (s<0) {
      printf("ERROR sem_wait()\n");
      exit(-1);     }

//------Se lee valor de semaforo -------------

  sem_getvalue(sem, &sval);
  printf("sem_wait: %d\n",sval);

//------Se decrementa semaforo -------------

  s = sem_wait(sem);
   
  if (s<0) {
      printf("ERROR sem_wait()\n");
      exit(-1);     }

//------Se lee valor de semaforo -------------

  sem_getvalue(sem, &sval);
  printf("sem_wait: %d\n",sval);

//------Se cierra semaforo -------------

   s=sem_close(sem);
   if (s) {
      printf("ERROR sem_close()\n");
      exit(-1);  }

//------Se elimina semaforo -------------

   s=sem_unlink("/sema1");
   if (s) {
      printf("ERROR sem_unlink()\n");
      exit(-1);  }

//--------------------------------------------
   
   pthread_join (hilo[0], NULL);
   pthread_join (hilo[1], NULL);
   
   printf("Fin del main() \n");

   pthread_exit (NULL);

}



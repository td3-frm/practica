/* productor-consumidor con semaforos */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUFFER          10  // Tamanio del buffer
#define DATOS_A_PRODUCIR    20

static int buffer[MAX_BUFFER] = {0};   // Buffer comun

pthread_t th1, th2;      // Hilos
sem_t *sem_dato, *sem_lugar;   // Semaforos

///////////////////////////////////////////////////////////////

void Productor(void) {     // PRODUCTOR

   int dato, i, pos, s;
   pos = 0;
   dato = 1000;                     // Producir dato
   int sem_val1, sem_val2;   
   
   for(i=0; i < DATOS_A_PRODUCIR; i++ ) {

      s = sem_wait(sem_lugar);            // Decrementa sem_lugar o esperar si igual a 0
      if (s != 0) {
        printf("ERROR; sem_wait() = %d\n", s);
        exit(-1);
      }
            
      dato++;
      buffer[pos] = dato;      
      pos = (pos + 1);

      if (pos >= MAX_BUFFER) {
      pos=0;   }

      sem_post(sem_dato);      // Incrementa sem_dato   
                   
      sem_getvalue(sem_lugar, &sem_val1);
      sem_getvalue(sem_dato, &sem_val2);
      printf("Productor  dato:%d, sem_lugar:%d, sem_dato:%d \n", dato, sem_val1,sem_val2);

   }
   
   printf("Termina Productor: %d\n",i);
   pthread_exit(0);

}
///////////////////////////////////////////////////////////////

void Consumidor(void){    // CONSUMIDOR

   int dato, i, pos, s;
   pos=0;
   int sem_val1, sem_val2;   
   
   for(i=0; i < DATOS_A_PRODUCIR; i++ ) {

	   s = sem_wait(sem_dato);            // Decrementa sem_dato o esperar si igual a 0
       if (s != 0) {
         printf("ERROR; sem_wait() = %d\n", s);
         exit(-1);
       }
       
      dato = buffer[pos];
      pos = (pos + 1) ;
      if (pos>= MAX_BUFFER) {
      pos=0;   }
      
     sem_post(sem_lugar);   // Incrementa sem_lugar   
     
      sem_getvalue(sem_lugar, &sem_val1);
      sem_getvalue(sem_dato, &sem_val2);
      printf("Consumidor dato:%d, sem_lugar:%d, sem_dato:%d \n", dato, sem_val1,sem_val2);
 
  }
  
  printf("Termina Consumidor: %d\n",i);
  pthread_exit(0);
}

///////////////////////////////////////////////////////////////

int main() {

   //int val;

   printf("Se crean semaforos\n");

//------ Crear semaforos -------------

   sem_lugar = sem_open("/sem_lugar", O_CREAT , 0666, MAX_BUFFER);
   if (sem_lugar == SEM_FAILED) {
      printf("ERROR sem_open()\n");
      exit(-1);     }

   sem_dato = sem_open("/sem_dato", O_CREAT , 0666, 0);
   if (sem_dato == SEM_FAILED) {
      printf("ERROR sem_open()\n");
      exit(-1);     }

   printf("Se crean hilos\n");

   pthread_create(&th1, NULL, (void *)&Productor, NULL);
   pthread_create(&th2, NULL, (void *)&Consumidor, NULL);

   pthread_join(th1, NULL);
   pthread_join(th2, NULL);

   sem_close(sem_dato);
   sem_close(sem_lugar);

   sem_unlink("/sem_dato");
   sem_unlink("/sem_lugar");

   printf("Termina main() \n");
   
   pthread_exit(0);
}

//------------------------------------------------------------//


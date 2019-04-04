/*  
 * Ejercicio 2 del TP Hilos
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int t = 0 ;
int arre[5]={0};

void *hola(void * nro) {
   sleep(2);
   printf("Hola, soy el hilo %d\n", * (int*) nro);
   pthread_exit(NULL);
}

int main() {
pthread_t hilo[5];
int rc;

  for(t=0; t < 5 ; t++){

     printf("Main creando el hilo nro %d\n", t);
     arre[t] = t;
     
     rc = pthread_create(&hilo[t], NULL, hola , (void *)(&t)  );
     //rc = pthread_create(&hilo[t], NULL, hola , (void *) (&arre[t]) );
     
     if (rc != 0){
         printf("ERROR; pthread_create() = %d\n", rc);
         exit(-1);        }
   }
  
   pthread_exit(NULL);

   printf("Esto no aparece!!!\n");
   
}

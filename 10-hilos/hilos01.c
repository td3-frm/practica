/*  
 * Ejercicio 1 de la guía práctica Hilos
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *hola(void * nro) {
   sleep(2);
   printf("Hola, soy el hilo %d\n", * (int*) nro);
   pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

pthread_t hilo[1];
int rc,t;

     t=0;
     printf("Main creando el hilo nro %d\n", t);
        
     rc = pthread_create(&hilo[0], NULL, hola , (void *)(&t)  );
     
     if (rc != 0){
         printf("ERROR; pthread_create() = %d\n", rc);
         exit(-1);        }
  
  
   printf("Espera a que termine hilo\n");

   pthread_join(hilo[0],NULL);

   printf("Termina hilo main\n");

   pthread_exit(NULL);

   
}

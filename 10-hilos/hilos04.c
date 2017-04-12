/*  
 * Ejercicio 4 del TP Hilos
 *   
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int suma=0;

void *hilo1 (void * nro)
{
   int numero, temp;
   
   numero = *(int*)nro;
   temp = suma;
   //usleep(300);
   //pthread_yield();
   temp = temp + 1 ;
   suma = temp;
   
   printf("Ejecutando hilo %d\n", numero);
   pthread_exit(NULL);
}

int main()
{
   pthread_t hilo[100];
   int rc, t, arre[100];

   for(t=0; t< 100 ; t++){
      printf("Creando el hilo %d\n", t);
      arre[t] = t;
      rc = pthread_create(&hilo[t], NULL, hilo1 , (void *)(&arre[t]) );
      if (rc){
         printf("ERROR; pthread_create() = %d\n", rc);
         exit(-1);
      }
   }

   int i;
   for (i=0; i<100;i++) {
       while(pthread_join(hilo[i], NULL));
   }
  
   printf("Valor de globlal = %d\n", suma);
      
   exit(0);
}

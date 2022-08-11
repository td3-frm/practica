/*  
 * Ejercicio 3 del TP Hilos
 *   
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t hilo[2];

void * hilo0()
{
  //pthread_detach(pthread_self());      
  printf ("Yo soy el hilo 0 \n");
  sleep(2);  
  pthread_exit (NULL);
}

void * hilo1()
{
  printf ("Yo soy el hilo 1 \n");
  printf("Esperando al hilo %lx \n", hilo[0]);
  
  pthread_join(hilo[0],NULL);
  printf("Terminando hilo 1 \n");
  pthread_exit (NULL);
}

int main()
{
  int rc;
  
  //Crear hilo 0
  rc = pthread_create (&hilo[0], NULL, hilo0, NULL);
  if (rc)
    {
      printf ("ERROR; pthread_create() = %d\n", rc);
      exit (-1);
    }    
  printf ("El main creando el hilo hola0, nro %lx\n",hilo[0]);
      
  //Crear hilo 1
  rc = pthread_create (&hilo[1], NULL, hilo1, NULL);  
  if (rc)
    {
      printf ("ERROR; pthread_create() = %d\n", rc);
      exit (-1);
    }    
  printf ("El main creando el hilo hola1, nro %lx\n",hilo[1]);
  
  pthread_join(hilo[1],NULL);
  printf ("Se ejecutaron todos los hilos\n");
  
  pthread_exit(NULL);
  //exit(0);
}

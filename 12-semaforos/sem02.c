#include <stdio.h>
#include <pthread.h>    
#include <unistd.h>
#include <stdlib.h>
//#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>   

int t, total, contador, s;
//sem_t *sem;

//------------------------------------------------------------

void *func_sem(void *nro)
{
   int local, j, numero,saldo;

   numero = *(int*)nro;

//------Se decrementa semaforo -------------

   for(j=0; j<contador; j++){

      local = total;
      local++;
      //usleep(1);
      total = local;
   }

   printf("Hilo %d, total = %d\n", numero,total);

   pthread_exit(NULL);
}

//------------------------------------------------------------

int main()
{
   int rc, n_hilos;
   int arre[10];
   
   total = 0;
   contador = 10;
   n_hilos = 10;
      
   pthread_t hilo[n_hilos];
   
   for(t=0; t < n_hilos; t++){
      
     arre[t] = t;

     rc = pthread_create(&hilo[t], NULL, func_sem , (void *)&arre[t]  ); // Se invoca hilo pasando variable t
     if (rc){
       printf("ERROR; pthread_create() = %d\n", rc);
       exit(-1);      }
  }

//-------------------------------------

   for(t=0; t < n_hilos; t++){
      
     pthread_join(hilo[t],NULL);   
  }
  
   printf("total = %d\n",total);

   pthread_exit(NULL);
}

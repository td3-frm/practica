/* uso de mutex */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



/* Variables Globales */

int t,total, vueltas,s ; 

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER; // inicializacion estatica del mutex


void *HILO0(void *nro) {
int numero;
   numero= *(int*)nro;

    s=pthread_mutex_lock(&mtx);         //bloqueo del mutex
   if (s!=0){
      printf("ERROR; pthread_mutex() = %d\n", s);
      exit(-1);   }

   total=total+numero;

   s=pthread_mutex_unlock(&mtx);      //desbloqueo del mutex
   if (s!=0){
      printf("ERROR; pthread_mutex() = %d\n", s);
      exit(-1);    }

   printf("Hilo 0, recibe nro=%d, total= %d\n",numero, total);
   pthread_exit(NULL);
}

int main() {

pthread_t hilo;
int rc ;
//int arre[5];
total=20;

     t=5;

     printf("Total= %d\n",total);
  
     printf("Main crea a hilo 0\n");
  
    
     rc = pthread_create(&hilo, NULL, HILO0 , (void *)&t  ); //llamo a HILO0 pasando la variable t
     if (rc){
       printf("ERROR; pthread_create() = %d\n", rc);
       exit(-1);    }


   s=pthread_mutex_lock(&mtx);         //bloqueo del mutex
   if (s!=0){
      printf("ERROR; pthread_mutex() = %d\n", s);
      exit(-1);   }

   total=total+t;

   s=pthread_mutex_unlock(&mtx);      //desbloqueo del mutex
   if (s!=0){
      printf("ERROR; pthread_mutex() = %d\n", s);
      exit(-1);    }

 
     pthread_join(hilo,NULL);


     printf("Total final= %d\n",total);

     pthread_exit(NULL);
}


/*
* Ejercicio 1 del TP de Cola de mensajes
* Tipica implementacion de una cola de mensajes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>

#define MENSAJE "DATA PARA OTROS PROCESOS"
#define MQ_PATH "/MQ_TD3"  // El nombre de la cola de mensajes debe empezar con "/"

int main() {
   
   int err, leido;
   char buff[1024];   
   mqd_t mqd; 
   struct mq_attr attr, attr_rcv;
   
   // Se fijan algunos parametros de la cola de mensajes antes de crearla
   attr.mq_msgsize = sizeof(buff);
   attr.mq_maxmsg = 5;
   
   // Se crea cola de mensajes
   mqd = mq_open(MQ_PATH, O_RDWR | O_CREAT, 0777, &attr); 
   if (mqd < 0) {
      printf ("error en mq_open()");   
      return -1; }
      
   printf("Cola de mensajes creada\n"); 
   
   // Se leen parametros de la cola de mensajes
   if (mq_getattr(mqd, &attr_rcv) == -1){
      printf ("error en mq_getattr()");
      return -1; }
      
   printf("Nro max. de mensajes en cola de mensajes: %ld\n",attr_rcv.mq_maxmsg);
   printf("Longitud max. de mensaje: %ld\n",attr_rcv.mq_msgsize);
   printf("Nros de mensajes pendientes en cola de mensajes: %ld\n",attr_rcv.mq_curmsgs);

   // Escribe en cola de mensajes
   err = mq_send(mqd, MENSAJE, strlen(MENSAJE)+1, 1);  //strlen nos da la longitud de una cadena
   if(err == -1){
      printf ("error en mq_send()");
      return -1;    }

   printf("Mensaje enviado (%d)\n", err);
   
   // Se lee de cola de mensajes
   leido = mq_receive(mqd, buff, attr.mq_msgsize, 0);
   if (( leido < 0 )){
      printf ("error en mq_receive()");
      return -1; }

   printf("Mensaje leido: %s\n", buff);
   
   // Se cierra cola de mensajes
   err = mq_close(mqd);
   if (( err < 0 )){
      printf ("error en mq_close()");
      return -1;   }

      printf("Cola de mensajes cerrada (%d)\n", err);
   
   // Se elimina cola de mensajes
   err = mq_unlink(MQ_PATH);
   if(err == -1){
      printf ("error en mq_unlink()");
      return -1;   }

      printf("Cola de mensajes eliminada (%d)\n", err);
      
   return 0;
}

/*
* Ejercicio 1 del TP de Cola de mensajes
* Tipica implementacion de una cola de mensajes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <mqueue.h>

#define MENSAJE "DATA PARA OTROS PROCESOS"
#define MQ_PATH "/MQ_TD3"  // El nombre de la cola de mensajes debe empezar con "/"

int main() {
   
   int err, leido;
   char buff[1024];   
   // const char buff[1024];   
   mqd_t mqd; 
   struct mq_attr attr, attr_rcv;
  
	// Se fijan algunos parametros de la cola de mensajes antes de crearla
	attr.mq_msgsize = sizeof(buff);
	attr.mq_maxmsg = 5;
   
	// Se crea cola de mensajes
	mqd = mq_open(MQ_PATH, O_RDWR | O_CREAT, 0777, &attr); 
	if (mqd < 0) {
		printf ("error en mq_open()\n");   
		exit(-1); }
      
	printf("Cola de mensajes creada\n"); 
   
<<<<<<< HEAD
   // Escribe en cola de mensajes
   err = mq_send(mqd, MENSAJE, strlen(MENSAJE)+1, 0);  //strlen nos da la longitud de una cadena
   if(err == -1){
=======
	// Escribe en cola de mensajes
	err = mq_send(mqd, MENSAJE, strlen(MENSAJE)+1, 1);  //strlen nos da la longitud de una cadena
	if(err == -1){
>>>>>>> 7b559016bdccbc607ddf093f127fd8c79c94e9e4
      printf ("error en mq_send()\n");
      exit(-1);    }

	printf("Mensaje enviado (%d)\n", err);
   
	// Se leen parametros de la cola de mensajes
	if (mq_getattr(mqd, &attr_rcv) == -1){
		printf ("error en mq_getattr()\n");
		exit(-1); }
      
	printf("Nro max. de mensajes en cola de mensajes: %ld\n", attr_rcv.mq_maxmsg);
	printf("Longitud max. de mensaje: %ld\n", attr_rcv.mq_msgsize);
	printf("Nros de mensajes pendientes en cola de mensajes: %ld\n", attr_rcv.mq_curmsgs);

<<<<<<< HEAD
   // Se lee de cola de mensajes
   leido = mq_receive(mqd, buff, attr_rcv.mq_msgsize, 0); 
   if (( leido < 0 )){
      printf ("error en mq_receive()\n");
      exit(-1); }
=======
	// Se lee de cola de mensajes
	leido = mq_receive(mqd, buff, attr_rcv.mq_msgsize, 0);
	if (( leido < 0 )){
		printf ("error en mq_receive()\n");
		exit(-1); }
>>>>>>> 7b559016bdccbc607ddf093f127fd8c79c94e9e4

	printf("Mensaje leido: %s\n", buff);
   
	// Se cierra cola de mensajes
	err = mq_close(mqd);
	if (( err < 0 )){
		printf ("error en mq_close()\n");
		exit(-1);   }

<<<<<<< HEAD
      printf("Cola de mensajes cerrada (%d)\n", err);
/* 
   // Se elimina cola de mensajes
   err = mq_unlink(MQ_PATH);
   if(err == -1){
      printf ("error en mq_unlink()\n");
      exit(-1);   }

      printf("Cola de mensajes eliminada (%d)\n", err);
 */    
   exit(0);
=======
	printf("Cola de mensajes cerrada (%d)\n", err);
   
	// Se elimina cola de mensajes
	err = mq_unlink(MQ_PATH);
	if(err == -1){
		printf ("error en mq_unlink()\n");
		exit(-1);   }

	printf("Cola de mensajes eliminada (%d)\n", err);
      
	exit(0);
>>>>>>> 7b559016bdccbc607ddf093f127fd8c79c94e9e4
}

/* 
programa SOCKET SERVIDOR de datagramas (UDP) el servidor envia al socket
lo que recibe del socket y lo muestra en pantalla: 
Cliente:--> datos rx socket
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int SockEscucha, sck_server, rx_socket, largo, cont;
char buffer_rx[256];
struct sockaddr_in struct_direccion={};

int main(int argc, const char *argv[])      {

   if (argc != 2){
       argv[1]="2000";
   } 


 //****************** 1 *******************//
 //-- socket(): Crear el socket -----------//
   SockEscucha=socket(AF_INET, SOCK_DGRAM, 0);
   
   if(( SockEscucha)<0) {
       printf ("ERROR en funcion socket()\n");
   exit(-1);     } 
   
   printf ("Paso 1: creo socket servidor\n");

//----- preparar el address:port -------------//
   struct_direccion.sin_family = AF_INET;
   struct_direccion.sin_addr.s_addr = htonl(INADDR_ANY);  // asigna una IP de la maquina
   struct_direccion.sin_port = htons(atoi (argv[1]));     // port pasado por argumento

 //****************** 2 *******************//
 //-- bind(): asociamos el socket a la direccion ------//

   if (bind (SockEscucha, (struct sockaddr *)&struct_direccion,sizeof(struct sockaddr_in))<0) {
       printf ("ERROR en funcion bind()\n");
   exit(-1);     } 

   printf ("Paso 2: Asociar bind() \n");

//****************** 3 *******************//
//-- servidor espera a recibir algo ---
   while(1) {  //lee del socket    

     int len=sizeof(struct_direccion);
     rx_socket = recvfrom(SockEscucha, buffer_rx, sizeof (buffer_rx), 0,(struct sockaddr*)&struct_direccion,&len);            //recibe del socket 

     if (rx_socket>0) {
        write (STDOUT_FILENO , "cliente:--> ", 12);      //escribe leyenda en pantalla
        write (STDOUT_FILENO , buffer_rx, rx_socket);      //escribe lo leido del socket
        sendto(SockEscucha, buffer_rx, rx_socket, 0, (struct sockaddr *) &struct_direccion, sizeof(struct_direccion)) ;                  //envia al socket lo que recibio

     }
 }

 //****************** 4 *******************//
 //------------cierrar la conexion --------// 

   close(sck_server); 
 
  return 0;
}  

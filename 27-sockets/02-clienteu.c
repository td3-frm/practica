/* 
programa SOCKET CLIENTE datagramas (UDP): cliente 
el cliente envia al socket lo que recibe por teclado y muestra en pantalla
socket: Servidor:--> datos rx socket 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 

int main(int argc , char const * argv[])
{
   char buff_tcl[256], buff_sck[56];
   struct sockaddr_in direccion={};
   int sockfd, lee_tcl, lee_sck, conn;

   if (argc != 2){
       argv[1]="2000";
   } 

//****************** 1 *******************//
 //-- socket(): Crear el socket -----------//

   sockfd=socket(AF_INET, SOCK_DGRAM, 0);

   if (sockfd==-1) { 
       printf ("ERROR en funcion socket()\n");
   exit(-1);     } 

   printf ("Paso 1: Se creo socket cliente\n");

   
//****************** 2 *******************//


//-- preparar el address:port del host servidor------//
   direccion.sin_family= AF_INET;
   direccion.sin_port=htons(atoi(argv[1])); 
//   inet_aton("localhost", &direccion.sin_addr); //convierte la direccion de Internet a una cadena de caracteres en la notacion estandar, Localhost = 127.0.0.1
   inet_aton("127.0.0.1", &direccion.sin_addr); //convierte la direccion IP a una cadena de caracteres en la notacion estandar
                                                //como el servidor esta en el mismo host usamos Localhost = 127.0.0.1

   printf ("Cliente va a enviar datos a IP: 127.0.0.1 Puerto: %s\n",  argv[1]);


//-- envia al socket datos --
  while(1){ 
 
    if (( lee_tcl = read(STDIN_FILENO, buff_tcl, sizeof (buff_tcl))) > 0) {     // lee de teclado
        sendto(sockfd, buff_tcl, lee_tcl, 0, (struct sockaddr *) &direccion, sizeof(direccion)); 
    }

   //-- recibe datos del socket -- 
     int len=sizeof(direccion);
     lee_sck = recvfrom(sockfd, buff_sck, sizeof (buff_sck), 0,(struct sockaddr *) &direccion,&len);
     write(STDOUT_FILENO, "Servidor:--> ", 13);               //escribe leyenda en pantalla
     write(STDOUT_FILENO, buff_sck, lee_sck);        //escribe lo leido del socket

  }

//****************** 3 *******************//
//------------cierrar la conexion --------// 

   close(sockfd);

   return 0;   
}

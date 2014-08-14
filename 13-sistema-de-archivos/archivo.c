#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main (){
	char buff[40] ;
	int fd, leido;
	// O_TRUNC deja el archivo en 0 bytes
	//fd = open ("archivo.dat",O_CREAT|O_RDWR|O_TRUNC,0600);
	// O_APPEND pone el offset al final luego de abrirlo
	//fd = open ("archivo.dat",O_CREAT|O_RDWR|O_APPEND,0600);
	fd = open ("archivo.dat",O_CREAT|O_RDWR,0600);
	// se desplaza .... si no hay datos, los pone en 0 (binario)
	lseek(fd,371 , SEEK_CUR);
	leido = read(fd,buff, 22);
	write (STDOUT_FILENO, buff, leido);
//	write (fd, "nuevosdatos" , 11);
	close(fd);
	return 0;

}

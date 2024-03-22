#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char buff_tcl[256];
int lee_tcl;
   
int main()
{
	printf("Hola Mundo!\n");
	printf("Ingrese nombre\n");

	lee_tcl = read(STDIN_FILENO, buff_tcl, sizeof (buff_tcl));
	write (STDOUT_FILENO, "Hola ", 5); 
    write (STDOUT_FILENO, buff_tcl, lee_tcl);   
	
 exit(0);

}

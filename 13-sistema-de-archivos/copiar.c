#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main (int argc, char * argv[]){

	struct stat sb;
	int entrada, salida,nro;
	char buff[1024];
	stat(argv[1], &sb);
        if (argc != 3) {
               fprintf(stderr, "Usage: %s <source> <dest>\n", argv[0]);
               exit(EXIT_FAILURE);
           }
	entrada = open (argv[1], O_RDONLY);
	salida  = open (argv[2], O_WRONLY|O_CREAT|O_TRUNC, sb.st_mode);
	while ((nro = read(entrada, buff, sizeof buff)) > 0){
		write(salida,buff, nro);
	}
	return 0;


}

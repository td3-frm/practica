/*
 * TP Procesos, Ejercicio 2 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PS_MACRO execl("/bin/sh", "sh", "-c", "ps -ef | grep proc_09", NULL);

int main()
{
    pid_t pid, ppid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork falló\n");
        exit(1);
        
    } else if (pid == 0) { // proceso hijo
        printf("Proceso hijo  (PID=%d) está corriendo.\n", getpid());
        
        sleep(1); 
        
        printf("Proceso hijo  (PID=%d) está saliendo.\n", getpid());

        exit(0);
    
    } else { // proceso padre
        
        printf("Proceso padre (PID=%d) está corriendo.\n", getpid());
        
        sleep(10); 
                
        printf("Proceso padre (PID=%d) está saliendo.\n", getpid());
        
        //~ wait(NULL);
    }
    
    return 0;
}


#
# TP Procesos, Ejercicio 7
#
import os
import multiprocessing

# Función que será ejecutada por el proceso hijo
def proceso_hijo():

    print("Proceso hijo ejecutándose con ID:", os.getpid())

    while True :
        pass
    
# Función principal que creará el proceso hijo y esperará a que termine
if __name__ == "__main__":

    # Crear proceso hijo
    hijo = multiprocessing.Process(target=proceso_hijo)

    hijo.start()

    print('PID del proceso padre : ' , os.getpid())
    print('PID del proceso hijo  : ' , hijo.pid)
    print('Nombre del proceso hijo : ' , hijo.name)

    # Esperar a que termine el proceso hijo
    # hijo.join()
    hijo.terminate()

    print("Proceso hijo finalizado")
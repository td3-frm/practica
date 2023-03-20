#
# TP Procesos, Ejercicio 8
#
import os
import multiprocessing

# Función que será ejecutada por el proceso hijo
def proceso_hijo():

    print("Proceso hijo ejecutándose con ID:", os.getpid())
    
    for i in range(5) :
        # Incrementar la variable compartida en el proceso hijo
        suma.value += 10

    print('Hijo, valor de suma : ' , suma.value)
    
# Función principal que creará el proceso hijo y esperará a que termine
if __name__ == "__main__":

    # Crear una variable compartida de tipo int con valor inicial 0
    suma = multiprocessing.Value('i', 0)
    
    # Crear proceso hijo
    hijo = multiprocessing.Process(target=proceso_hijo)

    hijo.start()

    for i in range(5) :
         # Incrementar la variable compartida en el proceso hijo
        suma.value += 1
    
    print('PID del proceso padre : ' , os.getpid())
    print('PID del proceso hijo  : ' , hijo.pid)
    print('Nombre del proceso hijo : ' , hijo.name)
    print('Padre, valor de suma : ' , suma.value)

    # Esperar a que termine el proceso hijo
    hijo.join()
    # hijo.terminate()

    print("Proceso hijo finalizado")
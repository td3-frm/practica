import os
import signal
import time

# Función para manejar la señal SIGINT (ctrl+c)
def sigint_handler(signum, frame):
    print('Has presionado Ctrl+C. Saliendo...')
    os._exit(0)

# Registrar el manejador de señales
signal.signal(signal.SIGINT, sigint_handler)

# Bucle infinito para simular un proceso en ejecución
if __name__ == '__main__':
    while True:
        print('El proceso está en ejecución.')
        time.sleep(2)

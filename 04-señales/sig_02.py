import os
import signal
import time

def sigint_handler(signum, frame):
    print('Has presionado Ctrl+C. Saliendo...')
    os._exit(0)

signal.signal(signal.SIGINT, sigint_handler)

def child_process():
    print('El proceso hijo ha comenzado.')
    while True:
        print('El proceso hijo está en ejecución.')
        time.sleep(2)
        
if __name__ == '__main__':
	
    print('El proceso padre ha comenzado.')
    
    pid = os.fork()

    if pid == 0:
        child_process()
    else:
        time.sleep(10)
        print('El proceso padre envía la señal SIGKILL al proceso hijo.')
        os.kill(pid, signal.SIGKILL)

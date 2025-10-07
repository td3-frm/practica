#
# Ejercicio 9 de TP Procesos
#

import os

ppid = os.getpid()

print("Proceso padre: %d:"%(ppid))
 
#Crea proceso hijo
os.fork()
#Crea proceso hijo
os.fork()

#todos los procesos pasan por acá
print("\nProceso: %d" % os.getpid())


 

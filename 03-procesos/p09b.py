#
# Ejercicio 9 de TP Procesos
#
import os
import multiprocessing

ppid = os.getpid()

print("Proceso unico:" , ppid)

#Crea proceso hijo
pid=os.fork()

#Analizar el resultado de fork
if pid==0 :
#al hijo le devuelve 0
	print("Hijo: " , os.getpid())
	print("Fork devuelve al hijo: ", pid)
		
else :
#Al padre le devuleve el pid del hijo 
	print("Padre: " , os.getpid())
	print("Fork devuelve al padre: ", pid)

#todos los procesos pasan por aca
print("Termina proceso: ", os.getpid())


 

#
# Ejercicio 9 de TP Procesos
#

import os
import multiprocessing
import math


# Crear una variable compartida de tipo int con valor inicial 0
suma = 0

ppid = os.getpid()

print("Proceso padre:" , ppid)

#Crea proceso hijo
pid=os.fork()

#Analizar el resultado de fork
if pid==0 :
#al hijo le devuelve 0
	print("ID Hijo: " , os.getpid())
	for i in range(5) :
		# Incrementar la variable compartida en el proceso hijo
		suma += 10
	print("Suma del proceso HIJO: ", suma)
		
else :
#Al padre le devuleve el pid del hijo 
	print("ID Padre: " , os.getpid())

	for i in range(5) :
		# Incrementar la variable compartida en el proceso hijo
		suma += 1
	print("Suma del proceso PADRE: ", suma)
	
#todos los procesos pasan por aca

if pid==0 :
	print("Termina hijo: ", os.getpid())
else :
	# Esperar a que termine el proceso hijo
	os.wait()
	
	 
	print("Termina padre: ", os.getpid())

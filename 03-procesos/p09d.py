#
# Ejercicio 9 de TP Procesos
#

import os
 

def ProcesoPadre():
	for i in range(1,10):
		print("Proceso Padre: %d"%(i))

	print("Fin funcion padre")

 

def ProcesoHijo():
	for i in range(1,10):
		print("Proceso Hijo: %d"%(i))

	print("Fin funcion hijo")

 
#-------------------------------
# Fork crea proceso hijo
pid = os.fork()


# Separa los procesos

if pid==0:
	print("Hijo, Fork= %d"%(pid))
	ProcesoHijo()

else:
	print("Padre, Fork= %d"%(pid))
	ProcesoPadre()


print("Todos los procesos pasan por aca: %d" %(os.getpid()))

if pid==0 :
	print("Termina hijo: ", os.getpid())
else :
	# Esperar a que termine el proceso hijo
	os.wait()
	
	 
	print("Termina padre: ", os.getpid())
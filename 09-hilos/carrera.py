import threading
import random
import time

# Función que simula la carrera de un auto
def correr_auto(nombre):
    distancia = 0
    while distancia < 100:
        # El auto avanza una distancia aleatoria
        avance = random.randint(1, 10)
        distancia += avance
        print(f"{nombre} ha avanzado {avance} metros y ha recorrido {distancia} metros en total.")
        # Esperar un tiempo aleatorio antes de avanzar de nuevo
        time.sleep(random.random())

# Lista de nombres de autos
nombres_autos = ["Auto 1", "Auto 2", "Auto 3", "Auto 4", "Auto 5"]

# Lista de hilos para representar cada auto
hilos_autos = []

# Crear un hilo para cada auto y agregarlo a la lista
for nombre in nombres_autos:
    hilo_auto = threading.Thread(target=correr_auto, args=(nombre,))
    hilos_autos.append(hilo_auto)

# Iniciar la carrera
for hilo_auto in hilos_autos:
    hilo_auto.start()

# Esperar a que todos los autos lleguen a la meta
for hilo_auto in hilos_autos:
    hilo_auto.join()

# Mostrar el resultado de la carrera
print("¡Carrera finalizada!")

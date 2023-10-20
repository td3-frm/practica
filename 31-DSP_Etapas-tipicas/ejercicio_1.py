import numpy as np
import matplotlib.pyplot as plt

# Parámetros de la señal
f = 100       # Frecuencia de la señal (Hz)
fs = 1000     # Frecuencia de muestreo (Hz)
t_start = 0   # Tiempo de inicio (s)
t_end = 0.01  # Tiempo de finalización (s)

# Generar vector de tiempos
t = np.arange(t_start, t_end, 1/fs)

# Generar señal senoidal
y = np.sin(2 * np.pi * f * t + np.pi/2)

# Graficar
plt.figure(figsize=(10,6))
plt.plot(t, y, '-o', markersize=5, label="Puntos de Muestreo")  # Agregar puntos
plt.title("Señal Senoidal")
plt.xlabel("Tiempo (s)")
plt.ylabel("Amplitud")
plt.grid(True)
plt.tight_layout()
plt.show()

dumb = 0
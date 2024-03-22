import os
import numpy as np
import matplotlib.pyplot as plt
import math
import scipy.io
import sounddevice as sd

from scipy.io import loadmat

from commpy.channels import awgn
from sklearn.metrics import mean_squared_error
from scipy.signal import lfilter
from scipy.signal import firwin
from scipy.signal import freqz

#Función de ruido
def my_awgn(signal, snr):

    # Calcular la potencia de la señal
    signal_power = np.mean(np.abs(signal) ** 2)

    # Calcular la potencia del ruido en función del SNR
    noise_power = signal_power / (10 ** (snr / 10))

    # Generar ruido blanco aditivo gaussiano
    noise = np.random.normal(0, np.sqrt(noise_power), len(signal))

    # Sumar el ruido a la señal
    noisy_signal = signal + noise

    return noisy_signal

#FUNCION GRAFICAR
def graficar_tiempo(tiempos, signal, titulo):
    plt.figure(figsize=(10,6))
    plt.plot(tiempos, signal, '-o', markersize=5, label="Puntos de Muestreo")  # Agregar puntos
    plt.title(titulo)
    plt.xlabel("Tiempo (s)")
    plt.ylabel("Amplitud")
    plt.grid(True)
    plt.tight_layout()
    plt.show()

def graficar_frec(frec, resp, titulo):
    plt.subplot(211)
    plt.plot(frec, np.abs(resp))   #Grafica MAGNITUD
    plt.title('Respuesta en frecuencia %s' %titulo)
    plt.xlabel('Frecuencia [radianes/muestra]')
    plt.ylabel('Amplitud [dB]')
    plt.grid()
    
    
    plt.subplot(212)
    plt.plot(frec, np.angle(resp))  #Grafica FASE
    plt.title('Fase %s' %titulo)
    plt.xlabel('Frecuencia [radianes/muestra]')
    plt.ylabel('Amplitud [dB]')
    plt.grid()
    plt.show()

#FILTRO FIR
def fir(fco,fs,ruido):
    
    N = round (math.sqrt(((0.885894**2)*(fs**2)/(fco**2))-1))  # Calculo orden del filtro
    valor = 1 / N

    # Diseñar los coeficientes del filtro FIR
    filter_coefficients = np.full (N, valor)   #Genero vector de N elementos de valor 1/N
    
    filtrada = lfilter (filter_coefficients, 1, ruido)
    
    return filtrada

#RESPUESTA EN FRECUENCIA Y FASE señal
def respuesta_signal(fs, signal, titulo):
    # Calcular la transformada de Fourier de la señal con ruido
    transformada = np.fft.fft(signal)

    #Respuesta en Frecuencia de la Señal con Ruido
    #frecuencias = np.fft.fftfreq(1000, 1/fs)
    frec = np.fft.fftfreq(len(transformada), 1/fs)
    graficar_frec(frec, transformada, titulo)


# Cargar el archivo "Tchaikovsky.mat"
data = loadmat('Tchaikovsky.mat')

# Cargar la matriz de datos de la clave 'signal'
signal = data['signal']

# Genera señal con ruido
noisy_signal = my_awgn(signal[:, 0], snr=50) #	Cambiar a menos para escuchar mejor el ruido

# Especificaciones del filtro
fs = 44100  # Frecuencia de muestreo
fco = 11050  # Frecuencia de corte del filtro (en Hz)

# Señal filtrada
signal_filtrada = fir(fco,fs,noisy_signal)

# Reproducir señal sin ruido
sd.play(signal[:, 0], fs)
sd.wait() # Espera a que termine la reproducción

# Reproducir señal con ruido
sd.play(noisy_signal, fs)
sd.wait() # Espera a que termine la reproducción

# Reproducir señal filtrada
sd.play(signal_filtrada, fs)
sd.wait() # Espera a que termine la reproducción

# Respuesta en frecuencia señal con ruido y la filtrada
respuesta_signal(fs, signal[:, 0],'señal sin ruido')
respuesta_signal(fs, noisy_signal,'señal con ruido')
respuesta_signal(fs, signal_filtrada,'señal filtrada')

import numpy as np
import matplotlib.pyplot as plt
import math

from scipy.signal import firwin
from scipy.signal import lfilter
from scipy.signal import freqz

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
    
#FUNCION RUIDO
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

#FILTRO FIR
def fir(frecuencia_signal,fs,ruido):
    #Frecuencia de corte
    fco=frecuencia_signal*2
    
    N = round (math.sqrt(((0.885894**2)*(fs**2)/(fco**2))-1))
    valor = 1 / N

    filter_coefficients = np.full (N, valor)   #Genero vector de N elementos de valor 1/N
    
    filtrada = lfilter (filter_coefficients, 1, ruido)
    
    return filtrada, filter_coefficients

#RESPUESTA EN FRECUENCIA Y FASE filtro
def respuesta_filtro(fs, filter_coefficients):
    frequencies, response = freqz(filter_coefficients, worN=8000, fs=fs)
    
    graficar_frec(frequencies, response, 'filtro')
    
    
#RESPUESTA EN FRECUENCIA Y FASE señal
def respuesta_signal(fs, signal, titulo):
    # Calcular la transformada de Fourier de la señal con ruido
    transformada = np.fft.fft(signal)

    #Respuesta en Frecuencia de la Señal con Ruido
    #frecuencias = np.fft.fftfreq(1000, 1/fs)
    frec = np.fft.fftfreq(len(transformada), 1/fs)
    graficar_frec(frec, transformada, titulo)
    
# Parámetros de la señal
f = 100       # Frecuencia de la señal (Hz)
fs = 1200     # Frecuencia de muestreo (Hz)
t_start = 0   # Tiempo de inicio (s)
t_end = 0.1  # Tiempo de finalización (s)

# Generar vector de tiempos
t = np.arange(t_start, t_end, 1/fs)

# Generar señal senoidal
y = np.sin(2 * np.pi * f * t + np.pi/2)

# Genera señal con ruido
noisy_signal = my_awgn(y, snr=10)

# Señal filtrada
signal_filtrada = fir(f,fs,noisy_signal)

# Respuesta en frecuencia filtro
respuesta_filtro(fs, signal_filtrada[1])
# Respuesta en frecuencia señal con ruido y la filtrada
respuesta_signal(fs, noisy_signal,'señal con ruido')
respuesta_signal(fs, signal_filtrada[0],'señal filtrada')

# Graficar
graficar_tiempo(t,y,"Señal Senoidal")
graficar_tiempo(t,noisy_signal,"Señal de ruido")
graficar_tiempo(t,signal_filtrada[0],"Señal Filtrada")


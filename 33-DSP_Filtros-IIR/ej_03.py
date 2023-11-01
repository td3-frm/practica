import scipy.signal as signal
import numpy as np
import matplotlib.pyplot as plt

# Parámetros del filtro
orden = 6
numtaps = 301  # Número de coeficientes
fs = 44100  # Frecuencia de muestreo
f1, f2 = 300, 3400  # Frecuencias de corte
rp = 0.5  # Ripple en la banda de paso en dB
rs = 60   # Atenuación en la banda de rechazo en dB

# Diseñar filtro FIR pasa-banda

fir_coefs = signal.firwin(numtaps, [f1, f2], pass_zero=False, fs=fs)

# Diseñar filtro IIR pasa-banda (Butterworth)
iir_coefs = signal.iirfilter(orden, [f1, f2], btype='band', ftype='butter', fs=fs)

# Respuesta en frecuencia de los filtros
w_fir, h_fir = signal.freqz(fir_coefs, worN=2000, fs=fs)
w_iir, h_iir = signal.freqz(iir_coefs[0], iir_coefs[1], worN=2000, fs=fs)

# Graficar respuesta en frecuencia de los filtros
plt.figure(figsize=(12, 6))

plt.subplot(2, 1, 1)
plt.plot(w_fir, 20 * np.log10(abs(h_fir)), label='FIR')
plt.plot(w_iir, 20 * np.log10(abs(h_iir)), label='IIR (Butterworth)')
plt.title('Respuesta en Frecuencia de los Filtros Pasa-Banda')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Amplitud [dB]')
plt.grid(True)
plt.legend()
plt.axvline(f1, color='red', linestyle='--')  # Frecuencia de corte inferior
plt.axvline(f2, color='red', linestyle='--')  # Frecuencia de corte superior
plt.xlim(0, fs/2)

# Graficar fase de los filtros
plt.subplot(2, 1, 2)
plt.plot(w_fir, np.angle(h_fir), label='FIR')
plt.plot(w_iir, np.angle(h_iir), label='IIR (Butterworth)')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Fase [radianes]')
plt.grid(True)
plt.legend()
plt.xlim(0, fs/2)

# Mostrar gráficos
plt.tight_layout()
plt.show()

import numpy as np
import matplotlib.pyplot as plt

def quantize_signal(signal, levels):
    # Determine the quantization levels
    min_val, max_val = np.min(signal), np.max(signal)
    quant_levels = np.linspace(min_val, max_val, levels)
    
    # Use digitize to map input signal to these levels
    quantized_indices = np.digitize(signal, quant_levels) - 1
    quantized_signal = quant_levels[quantized_indices]
    
    return quantized_signal

# Create a sine wave
t = np.linspace(0, 2, 1000, endpoint=False)
sine_wave = np.sin(2 * np.pi * 5 * t)

# Quantize the sine wave into 4 levels
quantized_sine = quantize_signal(sine_wave, 10)

# Graficar
plt.figure(figsize=(10,6))
plt.plot(t, quantized_sine, '-o', markersize=5, label="Puntos de Muestreo")  # Agregar puntos
plt.plot(t, sine_wave, '-x', markersize=5, label="Puntos de Muestreo")  # Agregar puntos

plt.title("Señal Senoidal")
plt.xlabel("Tiempo (s)")
plt.ylabel("Amplitud")
plt.grid(True)
plt.tight_layout()
plt.show()

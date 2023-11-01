import numpy as np
import matplotlib.pyplot as plt


def my_awgn(signal, snr):

    # Calculate signal power and convert to dB
    Ps = 10 * np.log10(np.mean(signal ** 2))

    # Calculate noise power and convert to dB
    Pn = Ps - snr

    # Generate noise
    noise = np.random.normal(0, np.sqrt(10 ** (Pn / 10)), signal.shape)

    # Add noise to signal
    signal_noisy = signal + noise

    return signal_noisy


# Create a sine wave
t = np.linspace(0, 2, 1000, endpoint=False)
sine_wave = np.sin(2 * np.pi * 5 * t)
snr = 30

signal_noisy = my_awgn(sine_wave, snr)

# Plot sine_wave and signal_noisy
plt.figure()
plt.plot(t, sine_wave, '-', label='Sine wave')
plt.plot(t, signal_noisy, '.', label='Noisy signal')
plt.legend()
plt.show()

dumb = 0
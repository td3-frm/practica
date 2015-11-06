
clear 
close all
clc

Fs = 1000;              % Sampling frequency, Hz
F1 = 50;                % Hz
F2 = 200;               % Hz

dt = 1/Fs;              % Sample time
N = 1024;               % Length of signal
t = (0:N-1)*dt;         % Time vector

% Sum of a 50 Hz sinusoid and a 120 Hz sinusoid
x = 1 + 0.7 * sin(2*pi*F1*t) + sin(2*pi*F2*t); 
y = x + 1 * randn(size(t));     % Sinusoids plus noise
plot(Fs * t(1:50), y(1:50))
title('Signal Corrupted with Zero-Mean Random Noise')
xlabel('time (milliseconds)')

[Y1, f, NFFT] = my_fft(y, Fs);

% Plot single-sided amplitude spectrum.
figure;

% plot(f, real(Y)) 
plot(f, (abs(Y1(1:NFFT/2+1)))) 

title('Single-Sided Amplitude Spectrum of y(t)')
xlabel('Frequency (Hz)')
ylabel('|Y(f)|')
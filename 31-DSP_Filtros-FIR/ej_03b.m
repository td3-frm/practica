clear 
close all
clc

load Tchaikovsky.mat

%% fir

Hd = fir_pb_300_3400;

a = 1;
b = Hd.Numerator;

signal_wn = filter(b, a, signal);

% sound(signal, Fs);
% sound(signal_wn, Fs);

%% PLOT

%% PLOT

[dft, f, dft_r, dft_i, dft_mag, dft_phase, NFFT] = my_dft(signal, Fs);
[dft, f_wn, dft_r, dft_i, dft_mag_wn, dft_phase, NFFT] = my_dft(signal_wn, Fs);

figure
subplot(2,1,1)
plot(f, dft_mag(:,1))
subplot(2,1,2)
plot(f_wn, dft_mag_wn(:,1), '--r')

figure 
freqz(b,a,256)


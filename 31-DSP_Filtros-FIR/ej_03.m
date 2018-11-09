clear 
close all
clc

% fn = 100;
% fs = 2000;
% 
% dt = 1/fs;
% 
% t = 0:dt:1;
% 
% signal = sin (2 * pi * fn * t);
% 
% snr = 10; % DB

% signal_n = mynoise(signal, snr);

load Tchaikovsky.mat

Hd = fir_pb_300_3400;
b = Hd.Numerator;
a = 1;

signal_wn = filter(b, a, signal);

% sound(signal_wn, Fs);

figure 
freqz(b,a,256)
 
 
%% PLOT

[dft, f, dft_r, dft_i, dft_mag, dft_phase, NFFT] = my_dft(signal, Fs);
[dft, f_wn, dft_r, dft_i, dft_mag_wn, dft_phase, NFFT] = my_dft(signal_wn, Fs);

figure
subplot(2,1,1)
plot(f, dft_mag(:,1))
subplot(2,1,2)
plot(f_wn, dft_mag_wn(:,1), '--r')



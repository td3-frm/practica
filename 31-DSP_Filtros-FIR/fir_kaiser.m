% fir_kaiser: FIR filter, Kaiser window
%
% Version: 001
% Date:    2016/11/10
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/td3

clc
close all
clear

%% FIR coefficients

load num_kaiser_50_75

% FIR order
M = max( size( num_kaiser_50_75));

% Pass-band frequencies
F1 = 300 ;
F2 = 3400 ;

% Signal/noise relationship (dB)
SNR = 60;

%% Audio signal
[signal, Fs] = audioread('Tchaikovsky_small.wav');

% sound(signal, Fs)

%% RUIDO

% signal_n = my_noise (signal, SNR);

% sound(signal_n, Fs)

%% FIR KAISER

% w5 = window(@kaiser, M, 7.5); 
% % hfvt =  wvtool(w5);
% W1 = (F1/Fs/2);
% W2 = (F2/Fs/2);
% Wn = [W1 W2];
% b = fir1(M-1, Wn, 'bandpass');

b = num_kaiser_50_75;
a = 1;            

signal_k = filter(b, a, signal);

sound(signal_k, Fs)

%% PLOT

%~ Plot the results: 
figure
plot(signal(:,1), 'ob', 'Linewidth', 2)
% hold on 
% plot(signal_n, '-g' , 'Linewidth', 2) 
hold on; 
plot(signal_k(round(M/2):end, 1), 'r' , 'Linewidth', 2)
legend('Senal original', 'Senal filtrada')
title('Comparacion de senales original y filtrada')
hold off

%% DATA FREQUENCY RESPONSE

[dft, f] = my_dft(signal, Fs);

[dft_k, f_k] = my_dft(signal_k, Fs);

figure
semilogy(f, abs(dft(:,1)) / max( abs(dft(:,1)) ), 'ob', 'Linewidth', 2); 
hold on
semilogy(f_k, abs(dft_k(:,1)) / max( abs(dft_k(:,1)) ), '-r', 'Linewidth', 2); 
% plot(f, abs(dft));
title('Respuesta en frecuencia del filtro FIR')
legend('Espectro senal original', 'Espectro senal filtrada')
hold off

%% FIR WINDOW FREQUENCY RESPONSE

% freqz: Frequency response of digital filter
% [H,W] = freqz(B,A,N) returns the N-point complex frequency response
% vector H and the N-point frequency vector W in radians/sample of
% the filter    

[Hf,f_k] = freqz(b, a, 256, Fs);

% Magnitud
HfA = abs(Hf);

%Fase
Hfphi = angle(Hf);

%~ Plot frequency response 
figure
semilogy(f_k, HfA/max(HfA), 'Linewidth', 2); 
% hold on
% plot(f, Hfphi, 'r');
legend('Magnitud', 'Fase')
title('Respuesta en frecuencia de la senal filtrada')
hold off
 


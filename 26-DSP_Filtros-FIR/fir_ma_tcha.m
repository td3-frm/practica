
clc
close all
clear

%% DATOS DE ENTRADA

% Orden del filtro MA
M = 5;

% Relacion senal/ruido (dB)
SNR = 30;

%% SENAL

% [signal, Fs] = audioread('Tchaikovsky_small.wav');
load Tchaikovsky_small.mat

% sound(signal, Fs)

%% RUIDO

signal_n = my_noise (signal, SNR);

% sound(signal_n, Fs)

%% FIR MA

%~ Enter the filter coefficients vector b:
b = ones(1,M)/M; 
a = 1;

signal_ma = filter(b, a, signal_n);

% sound(signal_ma, Fs)

%% PLOT

%~ Plot the results: 
figure
plot(signal(:,1), '--b', 'Linewidth', 2)
hold on 
plot(signal_n(:,1), '-g' , 'Linewidth', 2) 
hold on; plot(signal_ma( :, 1), 'r' , 'Linewidth', 2) % round(M/2) : end
legend('Señal original', 'Con ruido', 'Filtrada')

%% DATA FREQUENCY RESPONSE

[dft, f] = my_dft(signal, Fs);

[dft_ma, f_ma] = my_dft(signal_ma, Fs);

figure
semilogy(f, abs(dft(:,1)) / max( abs(dft(:,1)) ), 'ob', 'Linewidth', 2); 
hold on
semilogy(f_ma, abs(dft_ma(:,1)) / max( abs(dft_ma(:,1)) ), '-r', 'Linewidth', 2); 
% plot(f, abs(dft));
title('Respuesta en frecuencia del filtro FIR')
legend('Espectro senal original', 'Espectro senal filtrada')
hold off


%% FREQUENCY RESPONSE

% freqz: Frequency response of digital filter
% [H,W] = freqz(B,A,N) returns the N-point complex frequency response
% vector H and the N-point frequency vector W in radians/sample of
% the filter    

[Hf,f] = freqz(b, a, 256, Fs);

% Magnitud
HfA = abs(Hf);

%Fase
Hfphi = angle(Hf);

%~ Plot frequency response 
figure
plot(f, HfA); 
% hold on
% plot(f, Hfphi, 'r');
legend('Magnitud', 'Fase')
title('Respuesta en frecuencia y fase de FIR MA')



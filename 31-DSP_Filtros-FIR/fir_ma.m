% fir_ma: Moving Average FIR filter
%
% Version: 001
% Date:    2016/11/10
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/td3

clc
close all
clear

%% INPUT PARAMETERS

% MA FIR order
M = 10;

% Signal/noise relationship (dB)
SNR = 60;

%% INPUT SIGNAL

Fs = 44100;             % Frec. de muestreo, Hz
Fn = 100;               % Frec. senal 

N = 1000;               % Tamaño del vector tiempo

dt = 1/Fs;              % Tiempo de muestreo
t = (0:N-1)*dt;         % Vector tiempo
t = t';

signal = sin (2*pi*Fn*t);

%% ADD NOISE

signal_n = my_noise (signal, SNR);

%% MA FIR

% MAR FIR coefficients
b = ones(1,M)/M; 
a = 1;

signal_ma = filter(b, a, signal_n);

%% PLOT

figure
plot(signal, '--b', 'Linewidth', 2)
hold on 
plot(signal_n, '-g' , 'Linewidth', 2) 
hold on; 
% plot(signal_ma( round(M/2) : end), 'r' , 'Linewidth', 2)
plot(signal_ma, 'r' , 'Linewidth', 2)
legend('Señal original', 'Con ruido', 'Filtrada')


%% FREQUENCY RESPONSE

% freqz: Frequency response of digital filter
% [H,W] = freqz(B,A,N) returns the N-point complex frequency response
% vector H and the N-point frequency vector W in radians/sample of
% the filter    

[Hf,f] = freqz(b, a, 256, Fs);

% Magnitude
HfA = abs(Hf);

% Phase
Hfphi = angle(Hf);

% Frequency response 
figure
plot(f, HfA); 
hold on
plot(f, Hfphi, 'r');
legend('Magnitude', 'Phase')
title('Frequency and phase response from a MA FIR')


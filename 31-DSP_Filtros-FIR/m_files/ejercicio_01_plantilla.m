% Ejercicio 1 del trabajo practico Filtros FIR
%
% Version: 001
% Date:    2020/08/29
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/

clear
clc
close all

%% a) Genere una señal senoidal 

fs = 2000;
fn = 100;

dt = 1/fs;
P = 1/fn;
t = 0:dt:P*4; 
t = t';

signal = sin(2 * pi * fn * t) ;

%% b) Agregue ruido gaussiano a la señal senoidal

snr = 15;

[signal_n, var_n] = my_awgn (signal, snr);

% Verificar el valor de SNR
% SNR = 10 * log10 ( SIGNAL POWER / NOISE POWER )

SNR_test = 10 * log10(var(signal)/var(signal_n-signal))

%% c) Calcule el valor máximo del orden del filtro (N_max).

fco = fn * 2;

N_max = 

N_window_time = N_max * dt

%% d) Aplique filtrado del tipo moving average

% filter One-dimensional digital filter.
%     Y = filter(B,A,X) filters the data in vector X with the
%     filter described by vectors A and B to create the filtered
%     data Y.  The filter is a "Direct Form II Transposed"
%     implementation of the standard difference equation:
%  
%     a(1)*y(n) = b(1)*x(n) + b(2)*x(n-1) + ... + b(nb+1)*x(n-nb)
%                           - a(2)*y(n-1) - ... - a(na+1)*y(n-na)

M = N_max; 
a = 1;
b = ones(1, M) / M ; % Coeficientes de FIR MA

signal_ma = filter(b, a, signal_n);

%% e) Grafique la respuesta en frecuencia y fase del filtro MA

% freqz: Frequency response of digital filter
% [H,W] = freqz(B,A,N) returns the N-point complex frequency response
% vector H and the N-point frequency vector W in radians/sample of
% the filter 

freqz( b, a )

%% f) Grafique las señales en el dominio del tiempo sin ruido, con ruido y filtrada

figure

plot(t, signal, '--b')
hold on
plot(t, signal_n, '.r')
plot(t, signal_ma, '-g')
hold off

grid on

legend('Señal original', 'Con ruido', 'Filtrada')

%% h) Respuesta en frecuencia

[frq, mag] = my_dft(signal, fs);
[frq_n, mag_n] = my_dft(signal_n, fs);
[frq_ma, mag_ma] = my_dft(signal_ma, fs);

figure

plot(frq, mag, '-b')
hold on
plot(frq_n, mag_n, '.-r')
plot(frq_ma, mag_ma, '--g')
hold off

grid on

legend('Señal original', 'Con ruido', 'Filtrada')

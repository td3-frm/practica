% fir_matlab_to_C: script to compare FIR filters implemented in C and MATLAB
% languages.
%
% Version: 003
% Date:    2020/09/03
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/control

clc
close all
clear

%% Parametros

fn1 = 300;   % Signal 1 frequency
fn2 = 600;   % Signal 2 frequency
fn3 = 50;    % Signal 3 frequency, interference
fs = 10000;  % Sampling frequency

%% a) Genere una señal senoidal 

dt = 1/fs;
t = (0:dt:dt*1000)';

signal = sin(2 * pi * fn1 * t) + sin(2 * pi * fn2 * t);
signal_n = signal + 0.75 * sin(2 * pi * fn3 * t);

%% b) Transformar la señal a punto flotante precision simple

signal_f = single(signal_n);

%% c) Filtrado en C

signal_fir_c = fir_matlab_wrapper( signal_f );

%% d) Filtrado en MATLAB

Hd = fir_kaiser_200_800;
b = Hd.Numerator;
a = 1;

signal_fir_m = filter(b, a, signal_n);

%% Respuesta en el dominio del tiempo

figure
subplot(2,1,1)
plot(t, signal_n, '.-r')
grid on
legend('Señal con ruido')

subplot(2,1,2)
plot(t, signal, '-g')
hold on
plot(t, signal_fir_c, '--ob')
hold on
plot(t, signal_fir_m, '--om')
hold off

grid on
legend('Señal original', 'Señal filtrada en C', 'Señal filtrada en MATLAB' )

%% Respuesta en el dominio de la frecuencia

[f1, mag_n] = my_dft(signal_n, fs);
[f2, mag_fir] = my_dft(signal_fir_c, fs);

figure
plot(f1, mag_n, '.-r')
hold on
plot(f2, mag_fir, '--b')
hold off

grid on
legend('Señal con ruido', 'Señal filtrada')

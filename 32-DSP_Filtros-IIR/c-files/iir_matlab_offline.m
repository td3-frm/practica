% iir_matlab_to_C: script to compare IIR filters implemented in C and MATLAB 
% languages.
%
% Version: 002
% Date:    2018/04/10
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/control

clc
clear
close all

%% Parametros

fn1 = 1000;             % Signal 1 frequency
fn2 = 10000;            % Signal 2 frequency, interference
fs  = 44100;            % Sampling freq.

%% Genere una señal senoidal

tf = 0.005;             % Final time
dt = 1/fs;              % Sampling time
t = 0:dt:tf;            % Vector time
t = t';                 % Column vector

x1 = sin (2 * pi * fn1 * t);
x2 = sin (2 * pi * fn2 * t);

signal = x1;
signal_n = signal + 0.1 * x2;
 
%% Diseño filtro IIR

Hd = iir_elliptic_3400(fs);

%% Transformar la señal a punto flotante precision simple

% Input arguments must be in float

gain_f  = single(Hd.ScaleValues);
coeff_f = single(Hd.sosMatrix)';
signal_f = single(signal_n);

%% Filtrado en C, punto flotante precision simple

signal_iir_c = iir_matlab_wrapper( signal_f , coeff_f , gain_f );

%% Filtrado en MATLAB, punto flotante precision doble

SOS = Hd.sosMatrix;
G   = Hd.ScaleValues;

signal_iir_m = filtfilt(SOS, G, signal_n);

%% PLOT

% figure
% plot(t, x1, '-k')
% hold on
% plot(t, signal, '--b')
% plot(t, signal_iir_c, '--r')
% plot(t, signal_iir_m, '--g')
% hold off
% legend('ORIGINAL SIGNAL', 'NOISY SIGNAL', 'C-FUNCION OUTPUT', 'MATLAB OUTPUT')

%% Respuesta en el dominio del tiempo

figure
subplot(2,1,1)
plot(t, signal_n, '.-r')
grid on
legend('Señal con ruido')

subplot(2,1,2)
plot(t, signal, '-g')
hold on
plot(t, signal_iir_c, '--b')
hold on
plot(t, signal_iir_m, '--m')
hold off

grid on
legend('Señal original', 'Señal filtrada en C', 'Señal filtrada en MATLAB' )

%% Respuesta en el dominio de la frecuencia

[f1, mag_n] = my_dft(signal_n, fs);
[f2, mag_iir] = my_dft(signal_iir_c, fs);

figure
plot(f1, mag_n, '.-r')
hold on
plot(f2, mag_iir, '--b')
hold off

grid on
legend('Señal con ruido', 'Señal filtrada')

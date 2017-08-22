
clc
clear
close all

FS = 10000;      % Frecuencia de muestreo
FN = 100;       % Frecuencia de la senial

dt_s = 1/FS;

t = 2e-3:dt_s:0.3;     % vector que va de 0 a 0.1 en pasos de dt_s

% t_1c = 0:1/FS:0.01; 

y = sin(2 * pi * FN * t);
%y_1c = y(1:11);

plot(t, y, '-ob')

clc
close all
clear

% load Num

Fs = 48000;             % Frec. de muestreo, Hz
F1 = 100;               % Frec. senal 

N = 1000;               % Tamaño del vector tiempo

dt = 1/Fs;              % Tiempo de muestreo
t = (0:N-1)*dt;         % Vector tiempo

x1 = sin (2*pi*F1*t);
a = -0.1778;
b = 0.1778;
x2 = a + (b-a) .* rand(size(x1)); % 0.1778 ~ -15 dB
x = x1 + x2;

%~ Enter the filter coefficients vector b:
M = 10;
b = ones(1,M)/M; 
a = 1;

%~ Calculate transfer function Hf, its amplitude and phase on 256 samples, with fs=1:
[Hf,f] = freqz(b, a, 256, 1);
HfA=abs(Hf);      
Hfphi=angle(Hf);

%~ Plot frequency response 
figure
plot(HfA); 
title('Respuesta en frecuencia')

figure
plot(Hfphi, 'r');
title('Respuesta en fase')

%~ Apply the filter to x. Output is y:
y = filter(b, a, x);

%~ Plot the results: 
figure
% plot(x1(1:end), '--b'); hold on; plot(x(1:end), '-g'); hold on; plot(y, 'r')

plot(x1(1:end), '--b'); hold on; plot(x1(1:end-M/2+1), '-g'); hold on; plot(y(M/2:end), 'r')

legend('Señal original', 'Señal con ruido', 'Señal filtrada')

% Root mean squarred Errors
rms_sin_filtro = rmse (x1, x)

rms_con_filtro = rmse (x1(1:end-M/2+1), y(M/2:end)) 


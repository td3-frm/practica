

clear 
close all
clc

fn = 100;
fs = 2000;

dt = 1/fs;

t = 0:dt:1;

signal = sin (2 * pi * fn * t);

snr = 10; % DB

signal_n = mynoise(signal, snr);

%% MA

N = 100;
a = 1;
b = ones(1, N) / N;

signal_ma = filter(b, a, signal_n);

 
%% PLOT

figure
plot(t(1:20), signal(1:20), '-ob')
hold on
plot(t(1:20), signal_n(1:20),'--r')

figure
plot(t, signal, '-ob')
hold on
plot(t, signal_n,'--r')
plot(t, signal_ma,'--g')
legend('ORG', 'NOISE', 'MA')

figure 
freqz(b,a,256)


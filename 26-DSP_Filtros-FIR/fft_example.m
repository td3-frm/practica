
clc
clear
close all

Fs = 1600;

dt = 1/Fs;

t = 0:dt:100;

mysin = @(x, t)(x(2) * sin(2*pi*x(1)*t));
mycos = @(x, t)(x(2) * cos(2*pi*x(1)*t));

x1 = mysin([100, 1], t);
x2 = mysin([300, 1], t);
x3 = mysin([200, 1], t);
x4 = mysin([50,  1], t);

x = x1 + x2 + x3 + x4;

[dft, f, dft_r, dft_i, phase, NFFT] = my_dft(x', Fs);

figure
subplot(2,1,1)
plot(t(1:200), x(1:200))

subplot(2,1,2)
plot(f, dft_r)

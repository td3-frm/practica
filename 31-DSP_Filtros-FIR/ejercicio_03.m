

clc
clear
close all

load Tchaikovsky.mat

Hd = kaiser_bandpass;

B = Hd.Numerator;
A = 1;

signal_f = filter(B, A, signal(:,1));

[~, f, ~, ~, y_mag, ~, ~] = my_dft(signal(:,1), Fs);
[~, f_ka, ~, ~, y_mag_ka, ~, ~] = my_dft(signal_f(:,1), Fs);

figure
plot(f, y_mag(:,1), 'b')
hold on
plot(f_ka, y_mag_ka(:,1), 'r')
legend('ORIGINAL', 'FILTRADA')

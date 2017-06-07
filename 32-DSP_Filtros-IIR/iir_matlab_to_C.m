% iir_matlab_to_C: script to compare IIR filters implemented in C and MATLAB 
% languages.
%
% Version: 001
% Date:    2016/11/10
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/td3

clc
clear
close all

%% TIME

Fs  = 44100;            % Sampling freq.

tf = 0.005;             % Final time
dt = 1/Fs;              % Sampling time
t = 0:dt:tf;            % Vector time
t = t';                 % Column vector

%% INPUT SIGNAL

Fn1 = 1000;              % Signal freq.
x1 = sin (2 * pi * Fn1 * t);

Fn2 = 10000;              % Signal freq.
x2 = sin (2 * pi * Fn2 * t);

signal = x1 + 0.1 * x2;
 
%% NOISE

SNR = 60;

signal_n = my_noise (signal, SNR);

%% IIR

Hd = iir_elliptic_3400_44100;

%% MATLAB-to-C, SINGLE PRECISION

% Input arguments must be in float

gain_f  = single(Hd.ScaleValues);
coeff_f = single(Hd.sosMatrix)';
signal_f = single(signal_n);

output_c = iir_matlab_wrapper( signal_f , coeff_f , gain_f );

%% IIR MATLAB FILTERING, DOUBLE PRECISION

SOS = Hd.sosMatrix;
G   = Hd.ScaleValues;

output_m = filtfilt(SOS, G, signal_n);

%% PLOT

figure
plot(t, x1, '--k')
hold on
plot(t, signal_f, 'b')
hold on
plot(t, output_c, 'r')
hold on
plot(t, output_m, 'm')
hold off
legend('ORIGINAL SIGNAL', 'NOISY SIGNAL', 'C-FUNCION OUTPUT', 'MATLAB OUTPUT')

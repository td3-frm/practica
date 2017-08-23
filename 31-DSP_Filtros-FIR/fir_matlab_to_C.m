% fir_matlab_to_C: script to compare FIR filters implemented in C and MATLAB 
% languages.
%
% Version: 001
% Date:    2017/04/03
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/td3

clc
close all
clear

%% PARAMETERS

Fn1 = 500;   % Signal 1 frequency
Fn2 = 50;   % Signal 2 frequency, noise
Fs = 10000;  % Sampling frequency

%%

dt = 1/Fs;
t = (0:dt:pi)';

signal = sin(2 * pi * Fn1 * t) + 0.5 * sin(2 * pi * Fn2 * t); 

%% MATLAB-to-C, SINGLE PRECISION

% Input arguments must be in float

input_f = single(signal);

output_c = fir_matlab_wrapper( input_f );

%% FIR MATLAB FILTERING, DOUBLE PRECISION


%% PLOT

figure
plot(t, input_f, '--b')
hold on
plot(t, output_c, '-g')
legend('ORIGINAL', 'FILTRADA')

[~, f, ~, ~, y_mag, ~, ~] = my_dft(input_f(:,1), Fs);
[~, f_c, ~, ~, y_mag_c, ~, ~] = my_dft(output_c(:,1), Fs);

figure
plot(f, y_mag(:,1), 'b')
hold on
plot(f_c, y_mag_c(:,1), '--r')
legend('ORIGINAL', 'FILTRADA')


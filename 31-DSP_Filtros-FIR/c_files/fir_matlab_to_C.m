% fir_matlab_to_C: script to compare FIR filters implemented in C and MATLAB
% languages.
%
% Version: 002
% Date:    2019/04/15
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/control

clc
close all
clear

%% PARAMETERS

Fn1 = 200;   % Signal 1 frequency
Fn2 = 600;   % Signal 2 frequency
Fn3 = 50 ;   % Signal 3 frequency, interference
Fs = 10000;  % Sampling frequency

%%

dt = 1/Fs;
t = (0:dt:dt*2000)';

signal = sin(2 * pi * Fn1 * t) + sin(2 * pi * Fn2 * t) + 0.10 * sin(2 * pi * Fn3 * t);

%% MATLAB-to-C, SINGLE PRECISION

% Input arguments must be in float

signal_f = single(signal);

output_c = fir_matlab_wrapper( signal_f );

%% FIR MATLAB FILTERING, DOUBLE PRECISION

%% PLOT IN TIME

figure
subplot(2,1,1)
plot(t, signal_f, '-')
legend('ORIGINAL SIGNAL')
subplot(2,1,2)
plot(t, output_c, '-')
legend('FILTERED SIGNAL')

%% PLOT IN FREQ

[~, f1, ~, ~, H_signal_f, ~, ~] = my_dft(signal_f, Fs);
[~, f2, ~, ~, H_output_c, ~, ~] = my_dft(output_c, Fs);

figure
subplot(2,1,1)
plot(f1, H_signal_f, '-')
legend('ORIGINAL SIGNAL')
subplot(2,1,2)
plot(f2, H_output_c, '-')
legend('FILTERED SIGNAL')




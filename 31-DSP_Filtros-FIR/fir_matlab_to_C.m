% fir_matlab_to_C: script to compare FIR filters implemented in C and MATLAB 
% languages.
%
% Version: 002
% Date:    2019/11/08
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/td3

clc
close all
clear

lw = 3;

%% PARAMETERS

fn1 = 500;   % Signal 1 frequency
fn2 = 60;   % Signal 1 frequency
fs = 10000;  % Sampling frequency

%%

dt = 1/fs;
t = (0:dt:0.5)';

signal = sin(2 * pi * fn1 * t) + 0.5 * sin(2 * pi * fn2 * t); 

%% MATLAB-to-C, SINGLE PRECISION

% Input arguments must be in float

input_f = single(signal);

output_c = fir_matlab_wrapper( input_f );


%% PLOT

figure
plot(t, input_f, '-b', 'linewidth', lw)
hold on
plot(t, output_c, '-g', 'linewidth', lw)
legend('INPUT', 'FIR OUTPUT')
grid on

%% FREQUENCY RESPONSE

[f, dft_mag,]      = my_dft(signal, fs);

[f_fir, dft_mag_fir] = my_dft(output_c, fs);

figure
plot(f, dft_mag, '-b', 'linewidth', lw)
hold on
plot(f_fir, dft_mag_fir,'-g', 'linewidth', lw)
legend('INPUT', 'FIR OUTPUT')
grid on


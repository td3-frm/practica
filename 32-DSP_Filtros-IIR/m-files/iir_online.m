% iir_matlab_to_C: script to compare IIR filters implemented in C and MATLAB 
% languages.
%
% Version: 001
% Date:    2021/11/01
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/control

clc
clear
close all

%% PARAMETERS

Fn1 = 300;   % Signal 1 frequency
Fn2 = 600;   % Signal 2 frequency
Fn3 = 50 ;   % Signal 3 frequency, interference
Fs = 10000;  % Sampling frequency

%% INPUT SIGNAL

dt = 1/Fs;
t = (0:dt:dt*1000)';

adc_signal = sin(2 * pi * Fn1 * t) + sin(2 * pi * Fn2 * t) + 0.25 * sin(2 * pi * Fn3 * t);

% Input signal must be in float, not double
adc_signal_f = single(adc_signal);

%% MATLAB IIR FILTERING

Hd = irr_elliptic_200_800;

SOS = Hd.sosMatrix;
G   = Hd.ScaleValues;

iir_output_m = filtfilt(SOS, G, adc_signal);

%% C IIR FILTERING

s = size(adc_signal_f);
M = max(s);

iir_output = zeros(s); 

for j = 1:M
    
   iir_output (j) = iir_wrapper( adc_signal_f( j ) );
    
end

%% PLOT IN TIME

figure
subplot(2,1,1)
plot(t, adc_signal_f, '-b')
legend('INPUT SIGNAL')
grid on

subplot(2,1,2)
plot(t, iir_output_m, '-b')
hold on
plot(t, iir_output, '--r')
legend('IIR OUTPUT MATLAB', 'IIR OUTPUT C')
grid on

%% PLOT IN FREQ

[f1, mag_s ] = my_dft(adc_signal_f, Fs);
[f2, maf_f ] = my_dft(iir_output, Fs);
[f3, maf_m ] = my_dft(iir_output_m, Fs);

figure
plot(f1, mag_s, '-k')
hold on
plot(f2, maf_f, '--b')
plot(f2, maf_m, '--r')
legend('INPUT SIGNAL' , 'IIR OUTPUT MATLAB', 'IIR OUTPUT C')
grid on



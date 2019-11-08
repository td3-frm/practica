% EJ_03, Moving Average filter
%
% Version: 001
% Date:    2019/11/08
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>

clear 
close all
clc

lw = 3;

OS = 1; % OverSampling factor 

%% SIGNAL

fn = 100;       % signal frequency (Hz)
 
fs = 2000 * OS;     % sampling frequency (Hz)

dt = 1/fs;      % sampling time (s)

t = 0:dt:0.5;     % time vector (s)

signal = sin (2 * pi * fn * t); % input signal

%% NOISE

snr = 15;       % signal-noise ratio (dB)%% CUT OFF FREQUENCY

signal_n = my_noise(signal, snr);

%% CUT OFF FREQUENCY

fco = 150

Fco = fco / fs ;

% N = round( sqrt( 0.885894^2 +  Fco^2) / Fco )

N = round( sqrt( (0.885894^2 / Fco^2) -1 ) )

Fco_n = 0.885894 / sqrt( N^2 - 1 );

fco_n = Fco_n * fs


%% MA FILTER

a = 1;              % Denominator coefficients
b = ones(1, N) / N; % Numerator coefficients

signal_ma = filter(b, a, signal_n); % MA signal
 

%% PLOT

figure
plot(t, signal, '-b', 'linewidth', lw)
hold on
plot(t, signal_n,'--r', 'linewidth', lw)
plot(t, signal_ma,'-g', 'linewidth', lw)
legend('INPUT', 'NOISE', 'MA')

figure 
freqz(b, a, 2048)

[h, w] = freqz(b, a, 2048);

%% FREQUENCY RESPONSE

[f, dft_mag,]      = my_dft(signal_n, fs);

[f_ma, dft_mag_ma] = my_dft(signal_ma, fs);

figure
plot(f, dft_mag, '--r', 'linewidth', lw)
hold on
plot(f_ma, dft_mag_ma,'-g', 'linewidth', lw)
legend('NOISE', 'MA')


%% CORRECTED MA SIGNAL

delay = floor( N/2 );

G = max (signal) / max (signal_ma) * 1.1 ;

signal_d = signal(1:end-delay+1) ;
t_d = t(1:end-delay+1) ;

signal_ma_d = signal_ma(delay:end) * G ;
t_ma_d = t(1:end-delay+1) ;

figure
plot(t_d, signal_d, '-b', 'linewidth', lw)
hold on
plot(t_ma_d, signal_ma_d ,'-g', 'linewidth', lw)
legend('INPUT', 'MA')

%% RMSE (Root Mean Squared Error)

RMSE = rmse ( signal_d, signal_ma_d )


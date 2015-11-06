function [Y1, f, NFFT] = my_fft(y, Fs)

N = max(size(y));          % Length of signal

NFFT = 2^nextpow2(N); % Next power of 2 from length of y

% Y = fft(y,NFFT);
Y = fft(y,NFFT)/N;

% f = linspace(0, 1, NFFT);
% Y1 = Y;

% Y1 = Y(1:NFFT/2+1);
Y1 = Y;
Y1(2:end-1) = 2 * Y1(2:end-1);
f = Fs/2 * linspace(0, 1, NFFT/2+1);



function [dft, f, dft_r, dft_i, dft_mag, dft_phase, NFFT] = my_dft(data, Fs)
% my_dft: performs Discrete Fourier Transform
%
% Si la unidad de data es U, la unidad de la TDF entregada es U/Hz.
%
% INPUT:
%   data: señal de interes a analizar.
%   Fs: frecuencia de muestreo de data.
%
% OUTPUT:
%	dft   : transformada de Fourier discreta, valores complejos.
%   f     : vector frecuencia, en Hz.
%   dft_r : parte real transformada discreta de Fourier normalizada en frecuencia, en U/Hz.
%   dft_i : parte imaginaria transformada discreta de Fourier normalizada en frecuencia, en U/Hz.
%   dft_mag   : magnitud de la transformada discreta de Fourier.
%   dft_phase : fase de la transformada discreta de Fourier.
%   NFFT  : cantidad de elementos usados en la FFT.
%
% Version: 002
% Date:    2017/02/01
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>

L = max(size(data));        		% Tamaño de la señal

NFFT = 2^nextpow2(L);               % Potencia de 2 siguiente al tamaño del vector
f = Fs/2*linspace(0,1,NFFT/2+1);    % Vector frecuencia

dft = fft(data, NFFT) / L;

dft = dft(1:NFFT/2+1, :); % Se toman solo las frecuencias positivas

dft_r = real(dft);  % Parte real de la transformada discreta de Fourier
dft_i = imag(dft);  % Parte real de la transformada discreta de Fourier

dft_mag = abs(dft);	% Magnitud
dft_phase = angle(dft(1:NFFT/2+1, :));	% Fase

end


function [f, dft_mag, dft_phase, dft, NFFT] = my_dft(data, Fs)
% my_dft: devuelve la transformada discreta de Fourier de una serie de tiempo.
%
% Si la unidad de data es U, la unidad de la TDF entregada es U/Hz.
%
% INPUT
%   data: NxD serie de tiempo.
%   Fs: 1x1 frecuencia de muestreo de data.
%
% OUTPUT
%   f         : Nx1 vector frecuencia, en Hz.
%   dft_mag   : NxD magnitud de la transformada discreta de Fourier.
%   dft_phase : NxD fase de la transformada discreta de Fourier.
%	dft       : NxD transformada de Fourier discreta, valores complejos.
%   NFFT      : 1x1 cantidad de elementos usados en la FFT.
%
% Version: 003
% Date:    2019/05/08
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>

[n, m] = size(data);

if (m > n)							% Si data es un vector fila...
    
    data = data'; 					% Trasponer data
    n = m;
end

L = n;                              % Tamaño de la serie de tiempo

NFFT = 2^nextpow2(L);               % Potencia de 2 siguiente al tamaño del vector
f = Fs/2*linspace(0,1,NFFT/2+1);    % Vector frecuencia

dft = fft(data, NFFT) / L;          % Transformada rapida de Fourier

dft = dft(1:NFFT/2+1, :);           % Se toman solo las frecuencias positivas

dft_mag = abs(dft);                 % Magnitud
dft_phase = angle(dft);             % Fase

% dft_r = real(dft);  % Parte real de la transformada discreta de Fourier
% dft_i = imag(dft);  % Parte imaginaria de la transformada discreta de Fourier

end


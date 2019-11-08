function [signal_n, var_n] = my_noise (signal, snr)
% my_noise: adds noise to signal according to signal-noise relationship
% snr.
%
%   INPUT
%       signal: NxM vector, input signal.
%       snr:    signal-to-noise relationship in dB.
%
%   OUTPUT
%       signal_n: input signal with Gaussian white noise added.
%       std_n:    noise standard deviantion.  
%
% Version: 003
% Date:    2019/11/07
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/control

% Input signal order
[n,m] = size(signal);

if n < m
    signal = signal';
    [n,m] = size(signal);
end

% Input variance
var_s = var(signal);

% Noise variance
var_n = var_s / (10^( snr / 10 ));

% Standard deviation
std_n = sqrt( var_n );

% Standard deviation matrix
std_m =  ones(n,m);

for i=1:m
    std_m(:,i) = std_m(:,i) .* std_n(i);
end

% Add Gaussian white noise to input signal
signal_n = signal + randn(n,m) .* std_m;

end
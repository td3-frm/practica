function [signal_n, var_n] = my_noise (signal, snr)
% my_noise: adds noise to signal according to signal-noise relationship
% snr.
%
%   INPUT
%       signal: Nx1 vector, input signal.
%       snr:    signal-to-noise relationship in dB.
%
%   OUTPUT
%       signal_n: input signal with Gaussian white noise added.
%       std_n:    noise standard deviantion.  
%
% Version: 002
% Date:    2017/04/03
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/control

% Input variance
var_s = var(signal);

% Noise variance
var_n = var_s / (10^( snr / 10 ));

% Standard deviation
std_n = sqrt( var_n );

% Input signal order
[n,m] = size(signal);

% Standard deviation matrix
std_m =  ones(n,m);

for i=1:m
    std_m(:,i) = std_m(:,i) .* std_n(i);
end

% Add Gaussian white noise to input signal
signal_n = signal + randn(n,m) .* std_m;

end
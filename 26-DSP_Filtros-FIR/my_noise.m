function signal_n = my_noise (signal, snr)
% my_noise: adds noise to signal according to signal-noise relationship
% snr.
%
% Version: 001
% Date:    2016/11/10
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/td3

% Input variance
sig_s = var(signal);

% Noise variance
sig_n = sig_s / (10^( snr / 10 ));

% Standard deviation
std_n = sqrt( sig_n );

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
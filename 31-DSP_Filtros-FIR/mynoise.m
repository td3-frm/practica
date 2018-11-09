function signal_n = mynoise(signal, snr)

    n = length(signal);
    
    sigma_s = std(signal);
    
    sigma_n = sqrt ( sigma_s^2 / (10 ^ (snr/10) ) );

    noise = randn (1,n) * sigma_n;
    
    signal_n = signal + noise;
end
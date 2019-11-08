function signal_n = mynoise(signal, snr)

    n = length(signal);
    
    var_s = var(signal);
    
    var_n = sqrt ( var_s / (10 ^ (snr/10) ) );

    noise = randn (1,n) * sqrt(var_n);
    
    signal_n = signal + noise;
end
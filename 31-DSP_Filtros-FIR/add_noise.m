function signal_n = add_noise( signal, snr )

sigma_s = std(signal);

sigma_n = sigma_s / 10^(snr/20);

[m,n]= size(signal);

noise = sigma_n * randn(m,n);

signal_n = signal + noise;

end

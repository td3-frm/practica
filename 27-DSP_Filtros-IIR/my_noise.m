function signal_n = my_noise (signal, snr)

% Varianza senal de entrada
sig_s = var(signal);

% Varianza de ruido
sig_n = sig_s / (10^( snr / 10 ));

% Desviacion estandar
std_n = sqrt( sig_n );

% Tamano senal de entrada
[n,m] = size(signal);

% Matrix de desviacion estandar
std_m =  ones(n,m);

for i=1:m
    std_m(:,i) = std_m(:,i) .* std_n(i);
end

% Agregar ruido blanco gaussiano a senal de entrada
signal_n = signal + randn(n,m) .* std_m;

end
clear 
clc
close all

% [cancion, fs] = audioread ('Tchaikovsky.wav');
% [cancion, fs] = audioread ('Coldplay.wav');
% save cancion
% save fs

load cancion
load fs

[c1_dft, f1, c1_dft_r] = my_dft(cancion(:,1), 1/fs);

% Plot single-sided amplitude spectrum.
figure
semilogy(f1, 2*abs(c1_dft_r(:,1)) )
title ('Espectro original')

% ************************************************************************
% Pasa bajo
% ************************************************************************

% Hd = myfir_200_window_black;
Hd = myfir_bp_200_window_black_harris;
fir_lp = Hd.Numerator;

cancion_lp = filter(fir_lp, 1 ,cancion(:,1));
% cancion_fil = conv(cancion(:,1),fir,'same'); 

[c2_dft, f2, c2_dft_r] = my_dft(cancion_lp, 1/fs);

figure
semilogy(f2, 2*abs(c2_dft_r(:,1)) )
title ('Espectro aplicando filtro pasa bajos')

% ************************************************************************
% Moving average. Reduccion de ruido
% ************************************************************************
% fir_hp =  1- fir_lp;

cancion_ruido = cancion(:,1) + (0.1 * max(cancion(:,1))) .* rand(size (cancion(:,1)));
cancion_ruido = cancion_ruido ./ max(cancion_ruido);

M = 23;
fir_mav = 1/(M) .* ones(1,M+1);
superficie_rectangulo = trapz(fir_mav)
cancion_mav = filter(fir_mav, 1,cancion_ruido);

% ************************************************************************
% Reproduccion
% ************************************************************************

disp('Cancion original...')
sound(cancion,fs);

pause 

disp('Cancion afectada por filtro pasa bajos...')
sound(cancion_lp,fs);

pause 

disp('Cancion afectada por filtro pasa altos...')
sound(cancion_hp,fs);

pause 

disp('Cancion afectada por ruido...')
sound(cancion_ruido,fs);

pause 

disp('Cancion afectada por filtro moving average...')
sound(cancion_mav,fs);

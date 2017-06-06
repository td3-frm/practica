% irr_vs_fir: script to compare IIR and FIR filters performances for 
% similar frequency response.
%
% Version: 001
% Date:    2016/11/10
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/td3

clc
clear
close all

%% FIR

% fir_kaiser_3400_44100: funcion que disena un filtro FIR con ventana Kaiser

Hd_fir = fir_kaiser_3400_44100;

fir_coeff = Hd_fir.coefficients;

%% IIR

% iir_elliptic_3400_44100: funcion que disena un filtro IIR a partir de
% filtro analogico eliptico

Hd_iir = iir_elliptic_3400_44100;

iir_coeff = Hd_iir.coefficients;

%% PLOT

% fvtool: filter visualization tool

hfvt = fvtool(Hd_iir, Hd_fir, 'Analysis','Magnitude');
legend(hfvt,'IIR Elliptic', 'FIR Kaiser')

%% Questions

% 1) Compare both filters dimensions.
% 2) Plot the phases responses.
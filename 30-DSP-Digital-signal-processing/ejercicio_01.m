
clc
clear
close all

FS = 1000;
FN = 100;

dt_s = 1/FS;

t = 0:1/FS:1;

t_1c = 0:1/FS:0.01; 

y = sin(2 * pi * FN * t);
y_1c = y(1:11);

plot(t_1c, y_1c, '-ob')
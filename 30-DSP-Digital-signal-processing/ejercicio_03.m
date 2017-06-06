
clc
clear
close all

FN = 100;

FS = 10000;
t = 0:1/FS:1;
y = sin(2 * pi * FN * t);

% t_1c = 0:1/FS:0.01; C
% y_1c = y(1:11);

FS1 = 500;
t1 = 0:1/FS1:1;
y1 = sin(2 * pi * FN * t1);

FS2 = 110;
t2 = 0:1/FS2:1;
y2 = sin(2 * pi * FN * t2);

plot(t, y, '-b'), 
% hold on
% plot(t1, y1, '-og')
hold on
plot(t2, y2, '-xr')



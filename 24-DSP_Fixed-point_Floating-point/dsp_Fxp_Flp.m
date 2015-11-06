clc
clear
close all

u=linspace(-15,15,1000);

% Example 1
q=quantizer([6 4],'float');
range(q)
y1=quantize(q,u); 
figure
plot(u,y1);title(tostring(q))


% Example 2
q=quantizer('fixed',[7 2]); % [word-length fraction]
range(q)
y2=quantize(q,u);
figure
plot(u,y2);title(tostring(q))


%% PRECISION

format long

e1 = eps(single(1))
e2 = eps(single(1e1))
e3 = eps(single(1e10))

format bank
t  = single(1e10) +  single(1300)

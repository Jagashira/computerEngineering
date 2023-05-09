clear all
close all
% Load data points
load('Least_Square_Method_Ohm_problem3.mat');
I = current_data;
V = voltage_data;

err = @(x) sum((x(1) + x(2)*I - V).^2);

x0 = [0, 0]; 
x = fminsearch(err, x0);

I_range = linspace(min(I), max(I), 100);
V_est = x(1) + x(2)*I;
plot(I, V, '*', I_range, V_est, '-');
xlabel('Current - (A)');
ylabel('Voltage - (V)');
legend('given data', 'fitted line');
title("program3");
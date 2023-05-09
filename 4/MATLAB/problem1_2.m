% 1 Load the data points into MATLAB using the ‘load‘ function or by manually
% entering them as vectors.
%load('Least_Square_Method_Ohm_problem3.mat');
load('Least_Square_Method_Ohm.mat')

% 2 Create the design matrix ‘A‘ by stacking a column of ones and the ‘x‘ values
A = [ones(length(current_data),1), current_data];

% 3 Calculate the coefficients ‘a‘ and ‘b‘ using the ‘mldivide‘ function: ‘coeffs = A y‘
coeffs= mldivide(A,voltage_data);
b = coeffs(1);
a = coeffs(2);
yfit = a * current_data + b;

% 4 Plot the data points and the fitted line using the 4plot‘ function.
plot(current_data, voltage_data, '*', current_data, yfit);

xlabel('Current - (A)');
ylabel('Voltage - (V)');
legend('given data', 'fitted line');
title("program2");
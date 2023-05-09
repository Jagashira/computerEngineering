% 1 Construct the design matrix A and the target vector B
A = [1 1; 2 1; 3 1; 4 1];
B = [2; 4; 6; 8];

% 2 Compute the normal equations: ATAx = ATb.
ATA = A.' * A;
ATb = A.' * B;

% 3 Solve for x using matrix inversion and multiplication:
% x = (ATA)^-1 ATb.
x = inv(ATA) * ATb;

% 4 Disply the results in a graph.

plot(A(:,1), B,'*');
hold on;

x_vals = linspace(0, 5, 100);
y_vals = x_vals * x(1) + x(2);
plot(x_vals, y_vals);

xlabel('x');
ylabel('y');
title('program1');

hold off;
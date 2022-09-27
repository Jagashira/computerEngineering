y = zeros(1,10);
x = zeros(1,10);
h = 0.1;
y(1) = 1.0;
x(1) = 0.0;
y = exp(x);
for i = 1:100
    y(i+1) = y(i) + h*(-y(i));
    x(i+1) = x(i) + h;
end

xlabel('x')
ylabel('y')
title('Euler method',12)
plot(x,y,'--');
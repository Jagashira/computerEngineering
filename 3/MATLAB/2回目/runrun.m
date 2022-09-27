y = zeros(1,10);
x = zeros(1,10);
h = 0.1;
y(1) = 1.0;
x(1) = 0.0;
for i = 1:20
    k1 = h*y(i);
    k2 = h*(y(i) + k1/2);
    k3 = h*(y(i) + k2/2);
    k4 = h*(y(i) + k3);
    y(i+1) = y(i) + (k1 + 2*k2 + 2*k3 + k4)/6;
    x(i+1) = x(i) + h;
end
plot(x,y,"blue");


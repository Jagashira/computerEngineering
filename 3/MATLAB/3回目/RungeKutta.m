close all;
clear;
clc;

x1 = zeros(1,10);
x2 = zeros(1,10);

t = zeros(1,10);


h = 0.01;
x1(1) = 4;
x2(1) = -7;
t(1) = 0;

for i=1:1000
    k1 = h*func1(x1(i),x2(i));
    k2 = h*func1(x1(i)+h/2,x2(i)+k1/2);
    k3 = h*func1(x1(i)+h/2,x2(i)+k2/2);
    k4 = h*func1(x1(i)+h,x2(i)+k3);

    x1(i+1) = x1(i) + (k1+2*k2+2*k3+k4)/6;

    k1 = h*func2(x1(i),x2(i));
    k2 = h*func2(x1(i)+h/2,x2(i)+k1/2);
    k3 = h*func2(x1(i)+h/2,x2(i)+k2/2);
    k4 = h*func2(x1(i)+h,x2(i)+k3);

    x2(i+1) = x2(i) + (k1+2*k2+2*k3+k4)/6;

    t(i+1) = t(i) + h;

end


plot(t,x2,"--");
hold on
plot(t,x1);
xlabel("x")
title("機械振動系の数値解のグラフ")
legend({'x',"x'"},'Location','southeast')


function return_f = func1(~,x2)
    return_f = x2;
end

function return_f = func2(x1,x2)
    return_f = -2*x2-10*x1;
end

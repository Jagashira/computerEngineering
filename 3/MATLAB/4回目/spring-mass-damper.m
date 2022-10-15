%横軸
t_min = 0;
t_max = 50; %default 30
t = zeros(t_min+1,t_max);

% xの1乗、xの2乗
x1 = zeros(1,t_max);
x2 = zeros(1,t_min);

%微笑量
h = 0.01;

%繰り返し回数
count = t_max/h;

%初期値
x1(t_min+1) = 0;  %default x1 = 5 , 0
x2(t_min+1) = 5;  %default x2 = 0 , 5
t(1) = t_min;

%振動系の設定
m = 1;   % default m = 1
c = 5;   % default c = 5  c = 1 , 10 , -5
k = 10;  % default k = 5  k = 1 , 10

for i=1:count
    k1 = h*func1(x1(i),x2(i));
    k2 = h*func1(x1(i)+h/2,x2(i)+k1/2);
    k3 = h*func1(x1(i)+h/2,x2(i)+k2/2);
    k4 = h*func1(x1(i)+h,x2(i)+k3);

    x1(i+1) = x1(i) + (k1+2*k2+2*k3+k4)/6;

    k1 = h*func2(x1(i+1),x2(i),c,k);
    k2 = h*func2(x1(i+1)+h/2,x2(i)+k1/2,c,k);
    k3 = h*func2(x1(i+1)+h/2,x2(i)+k2/2,c,k);
    k4 = h*func2(x1(i+1)+h,x2(i)+k3,c,k);

    x2(i+1) = x2(i) + (k1+2*k2+2*k3+k4)/6;

    t(i+1) = t(i) + h;

end

plot(t,x1,"-o",'LineWidth',1);


function return_f = func1(~,x2)
    return_f = x2;
end

function return_f = func2(x1,x2,c,k)
    return_f = -c*x2-k*x1;
end

time=linspace(1,TIME,TIME);  %描画のため　高さの配列の初期化
plot(time,sin(time));
hold on;
plot(time,sin(time));
hold on;
plot(time,sin(time));
hold on;
plot(time,sin(time));
hold on;
legend("P制御","PI制御","PD制御","PID制御");

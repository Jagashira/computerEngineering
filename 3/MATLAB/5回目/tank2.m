%
%Sample program Tank2
%Hiroshi Takemura
%2022 10 11
%
close all;%グラフを消す
%*************************************
%** 初期値の設定 **
%*************************************
global R1 R2 A; %グローバル変数を定義
TIME = 1000;  %シミュレーションの計算回数
Kp = 20.0;       %比例ゲイン
Ki = 0.0;       %積分ゲイン 大きくしすぎない　0.1 ぐらいから試して！
Kd = 0.0;       %微分ゲイン　大きくしすぎない　1ぐらいから試して！
A  = 10.0;     %底面積
%*************************************
R1     = 1.0;  %バルブの抵抗R1
R2     = 1.0;  %バルブの抵抗R2
DELTA  = 0.1;  %きざみ幅 
INIT_Q = 0.0;  %qの初期値  
GOAL   = 1.0;  %目標高さ
%*************************************

%*************************************
%************************************%
%*****　　パラメーター設定　**********%
%************************************%
%**********%描画のため*****************
Goal_hight = 400; %描画のためゴールの高さ　ピクセル
tank_width = 300; %描画のためタンクの幅
tank_hight = 500; %描画のためタンクの高さ
Px1=50; Py1=50; Px2=Px1+tank_width; Py2=Py1+tank_hight; %描画のためタンクの大きさ
%*************************************
h1=0.0; h2=0.0; x=0.0; y=0.0; e=0.0; old_x=0.0; old_y=0.0; t=0.0; sum_e=0.0; 
d=0.0; q=INIT_Q;
tf=TIME; r = GOAL;     %目標高さ
h=DELTA; %刻み幅
%*************************************
hight_x=linspace(1,TIME,TIME); %描画のため　高さの配列の初期化
hight_y=linspace(1,TIME,TIME);%描画のため　高さの配列の初期化
time=linspace(1,TIME,TIME);  %描画のため　高さの配列の初期化
%*************************************%
%******計算しているのはここから********%
%*************************************%
for i = 1:TIME
    %qは流入量
    %2階の微分方程式を　ルンゲクッタ法を計算
    k1 = h*func1(x, q);
    k2 = h*func1(x+k1/2, q);
    k3 = h*func1(x+k2/2, q);
    k4 = h*func1(x+k3, q);

    x = x+(k1+2.0*k2+2.0*k3+k4)/6.0;
    if x<0 x=0; end %xはマイナスにならない
    
    k1 = h*func2(x, y);
    k2 = h*func2(x+h/2, y+k1/2);
    k3 = h*func2(x+h/2, y+k2/2);
    k4 = h*func2(x+h, y+k3);
    
    y = y+(k1+2.0*k2+2.0*k3+k4)/6.0;
    if y<0 y=0; end  %yはマイナスにならない

    e = (r-y);    %eは偏差  目標水位と現在の水位の差
    sum_e =(sum_e + e)/(1/h);             %sum_eは目標水位 rと現在の水位 xの積分
    d=((r-y)-(r-old_y));  %dは一つ前の偏差と現在の偏差との差

    %操作量の計算
    %操作量 Ｕの計算
    Up = Kp * e;              %比例制御の操作量 ゲイン Kp
    Ui = Ki * sum_e;          %積分制御の操作量 ゲイン Ki
    Ud = Kd * d;              %微分制御の操作量 ゲイン Kd
    U  = Up + Ui + Ud;        %制御量  PID制御

    %流入量の計算
    q = U+V();   

    %操作量の制限　制限するときはコメント外して！
    %if(q<0) q=0; end         %操作量の限界値　水は抜けない
    %if(q>A*1.5) q=A*1.5; end %操作量の限界値　底面積の1.3倍まで 適宜変更可！
    %if(x>r*1.1) q=0; end     %操作量の制限　　タンク１の水面高さの1.1倍までしか溢れられない

    old_y = y;              %old_xは一つ前の水位
    t=t+h;    %時間の更新

    hight_x(i)=x;
    hight_y(i)=y;
end

%描画　アニメーションのための準備
clf;%グラフを消す
fig=figure(1);
fig.ToolBar = 'none';
fig.Color = 'white';
axis([0 1000 0 700]);%グラフの軸設定　x軸:-10から10  y軸:-10から10
objx=rectangle('Position',[Px1 Py1 Px2-50 hight_x(1)],'FaceColor',[0 1 1]);%四角を描画
line([Px1 Px1],[Py1 Py2],'LineWidth', 3,'Color','black');%黒い線を描画　
line([Px1 Px2],[Py1 Py1],'LineWidth', 3,'Color','black');%黒い線を描画　
line([Px2 Px2],[Py1 Py2],'LineWidth', 3,'Color','black');%黒い線を描画　
line([Px1 Px2],[Py1+Goal_hight Py1+Goal_hight],'LineStyle',':','LineWidth', 3,'Color','black');%黒い線を描画　

objy=rectangle('Position',[Px1+450 Py1 Px2-50+450 hight_y(1)],'FaceColor',[0 1 1]);%四角を描画
line([Px1+450 Px1+450],[Py1 Py2],'LineWidth', 3,'Color','black');%黒い線を描画　
line([Px1+450 Px2+450],[Py1 Py1],'LineWidth', 3,'Color','black');%黒い線を描画　
line([Px2+450 Px2+450],[Py1 Py2],'LineWidth', 3,'Color','black');%黒い線を描画　
line([Px1+450 Px2+450],[Py1+Goal_hight Py1+Goal_hight],'LineStyle',':','LineWidth', 3,'Color','black');%黒い線を描画　

text(Px2+20+450,Py1+Goal_hight,'Gool','FontSize',14);
text(Px2+20+450,Py1,'Init.','FontSize',14);
ax = gca;%軸を再定義
ax.XAxis.Visible = 'off';%X軸のメモリを表示させない
ax.YAxis.Visible = 'off';%Y軸のメモリを表示させない

%実際のアニメーション
for i=1:tf
    if hight_x(i) < r 
        objx.FaceColor=[0 1 1];    %目標値より低いときの色
    else
        objx.FaceColor=[1 0 1];    %目標値より高いときの色
    end
    if hight_y(i) < r
        objy.FaceColor=[0 1 1];    %目標値より低いときの色
    else
        objy.FaceColor=[1 0 1];    %目標値より高いときの色
    end
    objx.Position=[Px1 Py1 Px2-50 hight_x(i)*400];
    objy.Position=[Px1+450 Py1 Px2-50 hight_y(i)*400];
    drawnow;
end

%*************************************%
figure(2);
plot(time*DELTA,hight_x,'*');%ルンゲクッタ法によるx(t)の計算結果
hold on; grid on;
plot(time*DELTA,hight_y,'o');%ルンゲクッタ法によるx(t)の計算結果
legend('x(t)','y(t)');
title('収束結果');
xlabel('time');
ylabel('Hight');
%*************************************%

%*************************************%
%** 関数の定義 ***********************%
function f=func1(x,q)
    global A R1;%グローバル変数を定義
    f=(*********);%自分で書き換えてください
end
function f=func2(x,y)
    global R1 R2 A;%グローバル変数を定義
    f=(*********);%自分で書き換えてください
end
%*************************************%

%*************************************%
%** ランダム関数の設定 **%
function d=V()
  %外乱を加えたい場合はコメントを外す 整数に無理やり変換
  %d= rand(1)*2-1;
  d=0;
end
%*************************************%
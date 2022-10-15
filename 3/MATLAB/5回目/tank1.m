%
%Sample program Tank1
%Hiroshi Takemura
%2022 10 11
%
clf;%グラフを消す
close all;%グラフを消す
%*************************************
%** 初期値の設定 **
%*************************************
TIME = 500;  %シミュレーションの計算回数
Kp = 1;       %比例ゲイン
Ki = 0;     %積分ゲイン 大きくしすぎない　0.1 ぐらいから試して！
Kd = 0;       %微分ゲイン　大きくしすぎない　1ぐらいから試して！
S  = 100;     %底面積
%*************************************

%************************************%
%************************************%
%*****　　パラメーター設定　**********%
%************************************%
%**********%描画のため*****************
Goal_hight = 400; %描画のためゴールの高さ　ピクセル
tank_width = 300; %描画のためタンクの幅
tank_hight = 500; %描画のためタンクの高さ
Px1=50; Py1=50; Px2=Px1+tank_width; Py2=Py1+tank_hight; %描画のためタンクの大きさ
%*************************************
h=0.1; t=0.0; x=0; e=0; old_x=0.0; sum_e=0.0; d=0.0;tf=TIME; r = 1.0;    %初期値
hight=linspace(1,TIME,TIME); %描画のため　高さの配列の書記か
time=linspace(1,TIME,TIME); %描画のため　高さの配列の書記か
%*************************************%
%******計算しているのはここから********%
%*************************************%
for i=1:tf
  e = r-x;                %eは偏差  目標水位と現在の水位の差
  sum_e =sum_e + e;       %sum_eは目標水位 rと現在の水位 xの積分
  old_x = x;              %old_xは一つ前の水位

  %操作量 Ｕの計算
  Up = Kp * e;            %比例制御の操作量 ゲイン Kp
  Ui = Ki * sum_e;        %積分制御の操作量 ゲイン Ki
  Ud = Kd * d;            %微分制御の操作量 ゲイン Kd
  U  = Up + Ui + Ud;      %制御量  

  %水位の計算
  x = x +(U + V())/S;     %V() は外乱 -1< V() < 1 のランダムな値 最初は無視
  d=x-old_x;              %dは一つ前の値と現在の値との差
  t=t+h;
  hight(i)=x;
end
%************************************
%******ここまで**********************
%************************************

%描画　アニメーションのための準備
clf;%グラフを消す
fig=figure(1);
fig.ToolBar = 'none';
fig.Color = 'white';
axis([0 700 0 700]);%グラフの軸設定　x軸:-10から10  y軸:-10から10
obj=rectangle('Position',[Px1 Py1 Px2-50 hight(1)],'FaceColor',[0 1 1]);%四角を描画
line([Px1 Px1],[Py1 Py2],'LineWidth', 3,'Color','black');%黒い線を描画　
line([Px1 Px2],[Py1 Py1],'LineWidth', 3,'Color','black');%黒い線を描画　
line([Px2 Px2],[Py1 Py2],'LineWidth', 3,'Color','black');%黒い線を描画　
line([Px1 Px2],[Py1+Goal_hight Py1+Goal_hight],'LineStyle',':','LineWidth', 3,'Color','black');%黒い線を描画　
text(Px2+20,Py1+Goal_hight,'Gool','FontSize',14);%　”Gool”を表示　
text(Px2+20,Py1,'Init.','FontSize',14);%　"Init.” を表示　
ax = gca;%軸を再定義
ax.XAxis.Visible = 'off';%X軸のメモリを表示させない
ax.YAxis.Visible = 'off';%Y軸のメモリを表示させない

%実際のアニメーション
for i=1:tf
    if hight(i) < r  %高さが目標値以下
        obj.FaceColor=[0 1 1];    %色を青にする
    else
        obj.FaceColor=[1 0 1];    %そうじゃなかったら　色を赤にする
    end
    obj.Position=[Px1 Py1 Px2-50 hight(i)*400];%四角の大きさを設定
    drawnow;   %四角を描画する
end

%*************************************%
figure(2);
plot(time,hight,'*');%x(t)の計算結果
legend('x(t)');
title('収束結果');
xlabel('time');
ylabel('Hight x(t)');
%*************************************%

%*************************************%
%** ランダム関数の設定 **%
function d=V()
  %外乱を加えたい場合はコメントを外す 
  %d= rand(1)*2-1;
  d=0;
end
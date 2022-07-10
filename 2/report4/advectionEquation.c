#include <stdio.h>
#include <math.h>
#include <string.h>

#define c 2.5
#define nx 200
#define nt  1000
#define dt 0.01
#define dx 0.1

double init(double x);
void array_copy(double u[200], double u_old[200]);
void array_display(double array[200], double count);

int main(){

    double u[nx] = {};
    double u_old[nx];

    //初期化
    for (int i = 0; i < nx; i++){
        u[i] = init(i * dx);
    }
    //main
    for (int i = 0; i < nt; i++){
        array_copy(u, u_old);
        for (int j = 1; j < nx - 1; j++){
            u[j] = (u_old[j] - c * (dt / dx) * (u_old[j] - u[j - 1]));
        }
        // printf("%lf\n",dt*i);

        // if (dt*i == 0||dt*i == 0.10000||dt*i == 1.000000||dt*i == 2.000000||dt*i == 4.000000||dt*i == 8.000000){
        if(i == 10||i == 100||i == 200||i == 400||i == 800){
            printf("%0.1lf\n",dt*i);
            array_display(u, nx);
        }
    }
}

double init(double x){
    printf("%lf\n",x);
    if (1 > x || x > 3){
        return 0;
    }else{
        return -(x - 1) * (x - 3);
    }


}


void array_copy(double u[nx], double u_old[nx]){
    for (int i = 0; i < 200; i++){
        u_old[i] = u[i];
    }
}

void array_display(double array[nx], double count){
    // 配列　表示
    for (int i = 0; i < count; i++){
        printf("%.1lf %lf \n", i*dx, array[i]);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 21
//拡散方程式　問題2
FILE *data[n], *gp, *data2[10];
char *data_file[n], *data_file2[10];
double init(double x);
// char *data_file0 , *data_file2 , *deta_file4 , data_file6 ;
// char str1[][12] = {"2-b-0.dat", "2-b-5.dat", "2-b-10.dat", "2-b-15.dat", "2-b-20.dat", "2-b-25.dat", "2-b-30.dat", "2-b-35.dat", "2-b-40.dat", "2-b-45.dat", "2-b-50.dat", "2-b-55.dat", "2-b-60.dat", "2-b-65.dat", "2-b-70.dat", "2-b-75.dat", "2-b-80.dat", "2-b-85.dat", "2-b-90.dat", "2-b-95.dat", "2-b-100.dat"};
char str1[][12] = {"2-d-0.dat", "2-d-5.dat", "2-d-10.dat", "2-d-15.dat", "2-d-20.dat", "2-d-25.dat", "2-d-30.dat", "2-d-35.dat", "2-d-40.dat", "2-d-45.dat", "2-d-50.dat", "2-d-55.dat", "2-d-60.dat", "2-d-65.dat", "2-d-70.dat", "2-d-75.dat", "2-d-80.dat", "2-d-85.dat", "2-d-90.dat", "2-d-95.dat", "2-d-100.dat"};
char str2[][12] = {"out2d1.dat", "out2d2.dat", "out2d3.dat", "out2d4.dat", "out2d5.dat", "out2d6.dat", "out2d7.dat", "out2d8.dat", "out2d9.dat", "out2d10.dat"};
int main()
{
    double **u;
    int i, j, k, p;
    // x,tの刻み幅
    double dt = 0.05; // 0.01  //0.05
    double dx = 0.2;
    // x,tの範囲　0<x<X  0<t<T
    double T = 100;
    double X = 10;
    //　x,t の要素数
    int tn = (T / dt) + 2;
    int xn = (X / dx) + 1;
    double r = dt / (dx * dx);
    /*
    int xn = 201;
    int tn = 1001;
    */
    // double x,y;
    // n = 200, m = 1000;
    /*動的にメモリ領域を確保*/
    u = malloc(sizeof(double *) * (xn + 1));
    for (i = 0; i <= xn + 1; i++)
    {
        u[i] = malloc(sizeof(double) * tn);
    }

    /*t=0 の時の初期条件を代入*/
    // u[0][0] = 1;
    // for (i = 1; i <= xn + 1; i++)
    // {
    //     u[i][0] = 0;
    // }
    for (int i = 0; i < xn; i++)
    {
        u[i][0] = init(i * dx);
    }
    /*u[x][t]からu[x][t+dt]の計算*/
    for (j = 0; j <= tn - 1; j++)
    {
        u[0][j] = 1;
        u[50][j] = 2;
        for (i = 1; i <= xn; i++)
        {
            u[i][j + 1] = r * u[i - 1][j] + (1 - 2 * r) * u[i][j] + r * u[i + 1][j];
        }
    }
    printf("%f\n", u[1][1]);
    printf("%d\n", tn);

    /*------ データファイル作成 ---------- */
    for (i = 0; i < n; i++)
    {
        data_file[i] = str1[i];
        data[i] = fopen(data_file[i], "w");
        int l = 5 * i / dt;
        for (k = 0; k <= xn; k++)
        {
            fprintf(data[i], "%f\t%f\n", k * dx, u[k][l]);
        }
        fclose(data[i]);
    }
    // for (i = 0; i < 10; i++)
    // {
    //     data_file2[i] = str2[i];
    //     data2[i] = fopen(data_file2[i], "w");
    //     int l = 5 * i / dt;
    //     for (k = 0; k <= xn; k++)
    //     {
    //         fprintf(data2[i], "%f\t%f\n", k * dx, u[k][l]);
    //     }
    //     fclose(data2[i]);
    // }

    /*------ グラフの作成 ---------- */
    /*
    gp = popen("gnuplot -persist","w");
    fprintf(gp, "set xrange [0:10]\n");
    fprintf(gp, "set yrange [-1:3]\n");
    fprintf(gp, "plot \"%s\" with lines linetype 1 title \"t=0\"\n",data_file);
    pclose(gp);
    */
    /*使用済みのメモリ領域を解放*/
    for (i = 0; i <= xn + 1; i++)
    {
        free(u[i]);
    }
    free(u);
    return 0;
}

double init(double x)
{
    // printf("%lf\n", x);
    if (x == 0)
    {
        return 1;
    }
    else if (x == 10)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}
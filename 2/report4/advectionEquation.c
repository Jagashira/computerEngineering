#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 4
#define Time 0
// void array_display(double array[nx][Time], double count, double dx);
//移流方程式　問題1 (d)
FILE *data[n], *gp;
char *data_file[n];
// char str1[][14] = {"out1d005.dat", "out1d01.dat", "out1d015.dat", "out1d02.dat"};
char str1[][14] = {
    "1-b-0.05.dat",
    "1-b-0.1.dat",
    "1-b-0.5.dat",
};

double init(double x)
{
    // printf("%lf\n", x);
    if (1 > x || x > 3)
    {
        return 0;
    }
    else
    {
        return -(x - 1) * (x - 3);
    }
}
int main()
{
    double **u;
    int i, j, k, p;
    double c = 2.5;
    // x,tの刻み幅
    double dt = 0.01;
    double dx;
    // x,tの範囲　0<x<X  0<t<T
    double T = 10;
    double X = 20;
    double count[6] = {0, 0.1, 1, 2, 4, 8};
    double xcount[3] = {0.05, 0.1, 0.5};

    for (p = 0; p <= 2; p++)
    {
        dx = xcount[p];
        //　x,t の要素数
        int tn = (T / dt) + 2;
        int xn = (X / dx) + 1;
        /*動的にメモリ領域を確保*/
        u = malloc(sizeof(double *) * (xn + 1));
        for (i = 0; i <= xn + 1; i++)
        {
            u[i] = malloc(sizeof(double) * tn);
        }

        /*t=0 の時の初期条件を代入*/
        for (int i = 0; i < xn; i++)
        {
            u[i][Time] = init(i * dx);
        }
        /// array_display(u[i][Time], xn, dx);

        /*u[x][t]からu[x][t+dt]の計算*/

        for (j = 0; j <= tn - 1; j++)
        {
            u[0][j + 1] = u[0][j] - c * dt / dx * (u[0][j] - 0);
            for (i = 1; i <= xn; i++)
            {
                u[i][j + 1] = u[i][j] - c * dt / dx * (u[i][j] - u[i - 1][j]);
            }
        }
        printf("%f\n", u[25][0]);
        printf("%d\n", xn);

        /*------ データファイル作成 ---------- */

        data_file[p] = str1[p];
        data[p] = fopen(data_file[p], "w");
        for (k = 0; k <= xn; k++)
        {
            fprintf(data[p], "%f\t%f\n", k * dx, u[k][400]);
        }
        fclose(data[p]);
        /*使用済みのメモリ領域を解放*/
        for (i = 0; i <= xn; i++)
        {
            free(u[i]);
        }
        free(u);
    }
    return 0;
}

// void array_display(double array[nx][Time], double count, double dx)
// {
//     // 配列　表示
//     for (int i = 0; i < count; i++)
//     {
//         printf("%.1lf %lf \n", i * dx, array[i][Time]);
//     }
// }
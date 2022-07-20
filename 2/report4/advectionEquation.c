#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//////////////////////////////////////////////////////////////
//出力するファイル数
#define n 3
///////////////////////////////////////////////////////////////

// void array_display(double array[nx][0], double count, double dx);

FILE *data[n], *gp;
char *data_file[n];
//  char file_list[][14] = {
//      "1-b-0.05.dat",
//      "1-b-0.1.dat",
//      "1-b-0.5.dat",
//  };
// char file_list[][100] = {
//     "1-b-0.dat",
//     "1-b-0.1.dat",
//     "1-b-1.dat",
//     "1-b-2.dat",
//     "1-b-4.dat",
//     "1-b-8.dat",
// };
char file_list[][100] = {
    "1-e-0.05.dat",
    "1-e-0.005.dat",
    "1-e-0.01.dat",

};

double init(double x);
// double key(double u[xn][0], double c, double T);
int main(){
    double **u;
    double c = 2.5;

    double dt_list[] = {
        0.05,
        0.005,
        0.01,

    };

    double dx = 0.1;
    double dt;

    double T = 10;
    double X = 20;
    // double count[n] = {0, 0.1, 1, 2, 4, 8};
    // double xcount[n] = {0.05, 0.1, 0.5};

    for (int p = 0; p < n; p++){

        dt = dt_list[p];

   
        int tn = (T / dt) + 2;
        int xn = (X / dx) + 1;
    
        u = malloc(sizeof(double *) * (xn + 1));
        for (int i = 0; i <= xn + 1; i++){
            u[i] = malloc(sizeof(double) * tn);
        }

        /*t=0 の時の初期条件を代入*/
        for (int i = 0; i < xn; i++){
            u[i][0] = init(i * dx);
        }
        /// array_display(u[i][0], xn, dx);

        // key(*u, c, 4);

        for (int j = 0; j <= tn - 1; j++){
            u[0][j + 1] = u[0][j] - c * dt / dx * (u[0][j] - 0);
            for (int i = 1; i <= xn; i++){
                u[i][j + 1] = u[i][j] - c * dt / dx * (u[i][j] - u[i - 1][j]);
            }
        }


        data_file[p] = file_list[p];
        data[p] = fopen(data_file[p], "w");
        for (int k = 0; k <= xn; k++){
            fprintf(data[p], "%f\t%f\n", k * dx, u[k][(int)(4 / dt)]);
        }
        fclose(data[p]);

        for (int i = 0; i <= xn; i++){
            free(u[i]);
        }
        free(u);
    }
    return 0;
}

// void array_display(double array[nx][0], double count, double dx)
// {
//     // 配列　表示
//     for (int i = 0; i < count; i++)
//     {
//         printf("%.1lf %lf \n", i * dx, array[i][0]);
//     }
// }

double init(double x){
    // printf("%lf\n", x);
    if (1 > x || x > 3){
        return 0;
    }else{
        return -(x - 1) * (x - 3);
    }
}

// double key(double u[xn][0], double c, double T)
// {
//     double x = c * T;
//     for (int i = 0; i < xn + 1; i++)
//     {
//         if (x <= i && x <= xn + 1 - x)
//         {
//             u[i][0] = u[i + x];
//         }
//     }
//     for (int i = 0; i < xn + 1; i++)
//     {
//         printf("%d %lf\n", i, u[i][0]);
//     }
// }
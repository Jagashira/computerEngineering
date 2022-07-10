#include <stdio.h>
#include <math.h>

#define n 3   //問題２の時nを6に変える
#define max 10000
#define epslon 1.0e-6

///////////////////////////////////////////////////////////////////
//自分で任意の値を代入する                              ////////////
//問題によって、aの値を3,1に変更する                    ////////////
#define a 5                                             ///////////
// SOR法を扱うとき任意の値を設定する                     ///////////
#define w 0.3                                           ///////////
// Jacobi法、Gauss-seidel法　SOR法それぞれを使うとき    ////////////
// boolの値を Jacobi=>0, Gauss=>1, SOR=>2 に変える      ////////////
#define bool 0                                          ///////////
///////////////////////////////////////////////////////////////////

void matrixOuput(double *matrix, double *b);
void marginForError(double xNew[n], double xOld[n], int count);

int main(){
    //問題１
    double matrix[n][n] = {
        {a, -3, 4},
        {3, -4 * a, 1},
        {4, -1, 3 * a},
    };
    double b[n] = {
        5857,
        5170,
        8049,
    };

    //問題２
    // double matrix[n][n] = {
    //     {1, cos(M_PI / 3), 0, 0, 0, 0},               // 2
    //     {0, -sin(M_PI / 3), 0, 0, 0, 0},              // 1
    //     {-1, 0, 1, cos(M_PI / 3), 0, -cos(M_PI / 3)}, // 4
    //     {0, 0, 0, sin(M_PI / 3), 0, sin(M_PI / 3)},   // 3
    //     {0, -cos(M_PI / 3), 0, 0, 1, cos(M_PI / 3)},  // 6
    //     {0, sin(M_PI / 3), 0, 0, 0, sin(M_PI / 3)},   // 
    // };
    // double b[n] = {
    //     0,
    //     -50, // 1
    //     0,
    //     0,
    //     0,
    //     0};

    double error;
    double xOld[n] = {};
    double xNew[n] = {};

    matrixOuput(*matrix, b);

    for (int count = 0; count < max; count++){
        error = 0.0;
        double xtmp[n];

        for (int i = 0; i < n; i++){
            #if (bool == 0 || bool == 1)
                xNew[i] = b[i];
            #else
                xtmp[i] = b[i];
            #endif

            for (int j = 0; j < n; j++){
                if (j != i){

                    #if (bool == 0)
                    // Jacobi法の時
                        xNew[i] -= matrix[i][j] * xOld[j];
                    #elif (bool == 1)
                    // Gauss-seidel法の時
                        xNew[i] -= matrix[i][j] * xNew[j];
                    #else
                    // SOR法の時
                        xtmp[i] -= matrix[i][j] * xNew[j];
                    #endif
                }
            }
            #if (bool == 0 || bool == 1)
                xNew[i] = xNew[i] / matrix[i][i];
            #else
                xtmp[i] /= matrix[i][i];
                xNew[i] = w * xtmp[i] + (1 - w) * xOld[i];
            #endif
        }
        marginForError(xNew, xOld, count);

        for (int i = 0; i < n; i++){
            error += fabs(xOld[i] - xNew[i]);
            xOld[i] = xNew[i];
        }

        if (error < epslon){
            break;
        }
    }

    for (int i = 0; i < n; i++){
        printf("x[%d] = %8.4f\n", i + 1, xNew[i]);
    }
    return 0;
}

void matrixOuput(double *matrix, double *b){

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("  %3.3lf  ", *(matrix + (n * i) + j));
        }

        printf("  =  ");
        printf("%.1lf", *(b + i));

        puts("");
    }
    puts("");
}

void marginForError(double xNew[n], double xOld[n], int count){
    double max_x[n];
    double maxValue;
    for (int i = 0; i < n; i++){
        max_x[i] = fabs((xNew[i] - xOld[i]) / xOld[i]);
    }
    maxValue = max_x[0];
    for (int i = 1; i < n; i++){
        if (maxValue < max_x[i]){
            maxValue = max_x[i];
        }
    }
    printf("%d %lf\n", count, log(maxValue));
}
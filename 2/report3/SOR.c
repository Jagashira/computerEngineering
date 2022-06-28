#include <stdio.h>
#include <math.h>

#define n 3
#define max 100
#define epslon 1.0e-6
#define a 5 //問題によって、aの値を3,1に変更する
#define w 0.3
void matrixOuput(double *matrix, double *b);
void marginForError(double xNew[3], double xOld[3], int count);

int main()
{
    double error;

    double matrix[n][n] = {
        {a, -3, 4},
        {3, -4 * a, 1},
        {4, -1, 3 * a},
    };

    double xOld[n] = {
        1.0,
        1.0,
        1.0};
    double xNew[n] = {};
    double b[n] = {
        5857,
        5170,
        8049,
    };

    matrixOuput(*matrix, b);

    for (int count = 0; count < max; count++)
    {
        double xtmp[3];
        error = 0.0;
        for (int i = 0; i < n; i++)
        {

            xtmp[i] = b[i];
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    xtmp[i] -= matrix[i][j] * xNew[j];
                }
            }
            xtmp[i] /= matrix[i][i];
            xNew[i] = w * xtmp[i] + (1 - w) * xOld[i];
        }
        marginForError(xNew, xOld, count);

        for (int i = 0; i < n; i++)
        {
            error += fabs(xOld[i] - xNew[i]);
            xOld[i] = xNew[i];
        }

        if (error < epslon)
        {
            break;
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%8.4f\n", xNew[i]);
    }

    return 0;
}

void matrixOuput(double *matrix, double *b)
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("  %3.3lf  ", *(matrix + (n * i) + j));
        }

        printf("  =  ");
        printf("%.1lf", *(b + i));

        puts("");
    }
    puts("");
}

void marginForError(double xNew[3], double xOld[3], int count)
{
    double max_x[3];
    double maxValue;
    for (int i = 0; i < n; i++)
    {
        max_x[i] = fabs((xNew[i] - xOld[i]) / xOld[i]);
    }
    maxValue = max_x[0];
    for (int i = 1; i < n; i++)
    {
        if (maxValue < max_x[i])
        {
            maxValue = max_x[i];
        }
    }
    printf("%d %lf\n", count, maxValue);
}
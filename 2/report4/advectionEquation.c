#include <stdio.h>
#include <math.h>

//#define c 2.5
double init(double x);
void array_copy(double u[200], double u_old[200]);
void array_display(double array[200], double count);

int main()
{

    int nx = 200;
    double dx = 0.1;
    int nt = 1000;
    double dt = 0.01;
    double c = 2.5;

    double u[200] = {};
    double u_old[200];
    for (int i = 0; i < nx; i++)
    {
        u[i] = init(i * dx);
    }

    for (int i = 0; i < nt; i++)
    {
        array_copy(u, u_old);
        for (int j = 1; j < nx - 1; j++)
        {
            u[j] = (u_old[j] - c * (dt / dx) * (u_old[j] - u[j - 1]));
        }

        if (i % 200 == 0)
        {
            array_display(u, 200);
        }
    }
}

double init(double x)
{
    // printf("%lf\n",x);
    if (1 > x || x > 3)
    {
        return 0;
    }
    else
    {
        return -(x - 1) * (x - 3);
    }
}

void array_copy(double u[200], double u_old[200])
{
    for (int i = 0; i < 200; i++)
    {
        u_old[i] = u[i];
    }
}

void array_display(double array[200], double count)
{
    // 配列　表示
    for (int i = 0; i < count; i++)
    {
        printf("%d %lf \n", i, array[i]);
    }
}

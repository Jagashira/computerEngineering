#include <stdio.h>
#include <math.h>
#define EPSILON 1e-6

double expression(double x);

int main()
{
    double a = 12, b = 100, c;
    int count = 0;

    if (expression(a) * expression(b) < 0)
    {
        do
        {
            count++;
            c = (a + b) / 2;
            if (expression(a) * expression(c) < 0)
            {
                b = c;

                printf("%d %lf\n", count, log(fabs(b - a)));
            }
            else
            {
                a = c;

                printf("%d %lf\n", count, log(fabs(b - a)));
            }

        } while (fabs(b - a) > EPSILON);

    }

    else
    {
        puts("NG\n");
    }

    return 0;
}

double expression(double x)
{
    return 0.033 * x * x * x - 5 * x * x + 210 * x - 2700;
}
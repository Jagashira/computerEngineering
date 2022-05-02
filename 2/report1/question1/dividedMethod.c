#include <stdio.h>
#include <math.h>
#define EPSILON 1e-6

double expression(double x);

int main()
{
    double a, b, c;
    int count = 0;

    puts("Please enter two numbers.");

    printf("a = ");
    scanf("%lf", &a);

    printf("b = ");
    scanf("%lf", &b);

    printf("f(a) = %lf\n", expression(a));
    printf("f(b) = %lf\n", expression(b));

    if (expression(a) * expression(b) < 0)
    {
        puts("OK\n");

        do
        {
            count++;
            c = (a + b) / 2;
            if (expression(a) * expression(c) < 0)
            {
                b = c;
                printf("a = %.3lf, b = %.3lf   count:%d\n", a, b, count);
            }
            else
            {
                a = c;
                printf("a = %.3lf, b = %.3lf   count:%d\n", a, b, count);
            }

        } while (fabs(b - a) > EPSILON);

        puts("result:");
        printf("a = %.7lf\n", a);
        printf("b = %.7lf\n", b);
        printf("The number of trials is %d", count);
    }

    else
    {
        puts("NG");
        return 1;
    }

    return 0;
}

double expression(double x)
{
    return 0.033 * x * x * x - 5 * x * x + 210 * x - 2700;
}
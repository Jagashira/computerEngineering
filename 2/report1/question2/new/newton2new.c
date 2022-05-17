#include <stdio.h>
#include <math.h>
#define EPSILON 1e-6
#define G 9.8

double expression(double x);
double expression_d(double x);

int main()
{
    double a, b, e;
    int count = 0;

    puts("Please enter number.");

    printf("a = ");
    scanf("%lf", &a);
    b = a;

    do
    {
        count++;
        a = a - (expression(a) / expression_d(a));
        printf("a = %.3lf   count:%d\n", a, count);

        e = fabs(expression(a));
    } while (e > EPSILON);

    printf("e = %.8lf\n", e);

    puts("result:");
    printf("a = %.7lf\n", a);
    printf("The number of trials is %d", count);

    return 0;
}

double expression(double x)
{
    return (-(G * x * x) / 2) + 25 * x - 5;
}

double expression_d(double x)
{
    return -(G * x) + 25;
}
#include <stdio.h>
#include <math.h>
#define EPSILON 1e-6

double expression(double x);
double expression_d(double x);

int main()
{
    double a, b, marginForError;
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
        // printf("%d %lf",count,a);

        marginForError = fabs(expression(a));
    } while (marginForError > EPSILON);

    printf("margin For error = %.8lf\n", marginForError);

    puts("result:");
    printf("a = %.7lf\n", a);
    printf("The number of trials is %d", count);

    return 0;
}

double expression(double x)
{
    return 0.033 * x * x * x - 5 * x * x + 210 * x - 2700;
}

double expression_d(double x)
{
    return 0.099 * x * x - 10 * x + 210;
}
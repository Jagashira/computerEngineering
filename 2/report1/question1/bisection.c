#include <stdio.h>
#include <math.h>
#define epsilon 1.0 / 1000000

double f(double x)
{
    return 0.033 * x * x * x - 5 * x * x + 210 * x - 2700;
}

int main()
{
    double a, b, c;
    int count = 0;

    printf("a = ");
    scanf("%lf", &a);

    printf("b = ");
    scanf("%lf", &b);

    if (f(a) * f(b) < 0)
    {
        do
        {
            count++;
            c = (a + b) / 2;
            if (f(a) * f(c) < 0)
            {
                b = c;
                //     printf("%count a = %lf, b = %lf\n", count, a, b);
            }
            else
            {
                a = c;
                // printf("%d a = %lf, b = %lf\n", d, a, b);
            }
            // printf("%d %lf\n", d, log(fabs(b - a)));
            printf("%d a = %lf, b = %lf\n", count, a, b);
        } while (fabs(b - a) > epsilon);

        printf("a = %.7lf\n", a);
        printf("b = %.7lf\n", b);
    }
    else
    {
        return 0;
    }

    return 0;
}

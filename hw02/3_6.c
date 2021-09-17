#include <stdio.h>

#define TRUTH_VALUE (6.737947e-3)
#define TERMS (20)

void method1(double x, int terms, double values[])
{
    double sum = 0;
    double numerator = 1, denom = 1;
    for (int i = 0; i < terms; ++i)
    {
        sum += numerator / denom;

        numerator *= x;
        denom *= i + 1;

        values[i] = sum;
    }
}

void method2(double x, int terms, double values[])
{
    double sum = 0;
    double numerator = 1, denom = 1;
    for (int i = 0; i < terms; ++i)
    {
        sum += numerator / denom;

        numerator *= -x;
        denom *= i + 1;

        values[i] = 1. / sum;
    }
}

int main()
{
    void (*methods[2])(double, int, double[]) = { method1, method2 };
    
    for (int i = 0; i < 2; ++i)
    {
        printf("[Method %d]\n", i + 1);
        double values[TERMS];
        i[methods](-5, TERMS, values);

        for (int i = 0; i < TERMS; ++i)
        {
            printf("iter %d approx %lf err_a ", i, values[i]);
            
            if (i > 0)
                printf("%lf ", (values[i - 1] - values[i]) / values[i - 1]);
            else
                printf("na ");

            printf("err_r %lf\n", (TRUTH_VALUE - values[i]) / TRUTH_VALUE);
        }
        
        printf("\n");
    }
}

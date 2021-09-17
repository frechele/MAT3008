#include <stdio.h>
#include <math.h>

#define TRUTH_VALUE ((double)0.5)

int main()
{
    const double PI = acos(-1);

    double prev = 0, sum = 0;
    double numerator = 1, denom = 1;
    for (int i = 0; ; ++i)
    {
        prev = sum;
        sum += numerator / denom;

        numerator *= -(PI * PI) / 9;
        denom *= (2 * i + 1) * (2 * i + 2);

        printf("iter %d approx %lf err_a ", i, sum);
        
        if (i > 0)
            printf("%lf ", (prev - sum) / sum * 100.);
        else
            printf("na ");

        printf("err_r %lf\n", (TRUTH_VALUE - sum) / TRUTH_VALUE * 100.);
    }
}

#include <stdio.h>
#include <math.h>
#include "nr.h"

#define MAX_BRACKETS ((int)1e7)
#define MAX_ROOTS (100)

float f_8_32(float x)
{
    const float e_0 = 8.85e-12f;
    const float q = 2e-5f;
    const float Q = 2e-5f;
    const float a = 0.9f;

    return 1 / (4 * acos(-1) * e_0) * q * Q * x / ((x*x + a*a) * sqrt(x*x + a*a)) - 1;
}

float f_8_36(float T)
{
    return 0.99403 + 1.671 * 1e-4 * T + 9.7215 * 1e-8 * T * T - 9.5838 * 1e-11 *T*T*T + 1.9520 * 1e-14 * T*T*T*T - 1.2;
}

float muller(float (*f)(float), float x1, float x2, float xacc, int* n_iter);

void solve(float (*f)(float), float x1, float x2)
{
    float xb1[MAX_ROOTS], xb2[MAX_ROOTS];
    int numOfRoots = MAX_ROOTS;
    zbrak(f, x1, x2, MAX_BRACKETS, xb1, xb2, &numOfRoots);

    printf("roots (%d) = ", numOfRoots);

    int nIter;
    for (int i = 1; i <= numOfRoots; ++i)
    {
        printf(" %.6f", muller(f, xb1[i], xb2[i], 1e-6, &nIter));
    }

    printf("\n\n");
}

int main()
{
    int n_iter;

    printf("problem 8.32\n");
    solve(f_8_32, 0, 2);

    printf("problem 8.36\n");
    solve(f_8_36, 800.f, 1500.f);
}

#include <stdio.h>
#include <math.h>
#include "nr.h"

#define X_MIN (200.f)
#define X_MAX (400.f)

float f(float R)
{
    return exp(-0.005 * R) * cos(sqrt(2000 - 0.01 * R*R) * 0.05) - 0.01;
}

float df(float R)
{
    return exp(-0.005 * R) * ((0.0005 * R * sin(sqrt(2000 - 0.01 * R*R) * 0.05)) / sqrt(2000 - 0.01 * R*R) - 0.005 * cos(sqrt(2000 - 0.01 * R*R) * 0.05));
}

void f_df(float R, float* y, float* grad)
{
    *y = f(R);
    *grad = df(R);
}

float muller(float (*f)(float), float x1, float x2, float xacc, int* n_iter);

float run(float (*solver)(float (*)(float), float, float, float, int*), float x1, float x2, float xacc, int* n_iter);
float run_diff_method(float (*solver)(void (*)(float, float*, float*), float, float, float, int*), float x1, float x2, float xacc, int* n_iter);

#define NUM_OF_METHODS (6)

const char* METHOD_NAMES[NUM_OF_METHODS] = {
    "bisection",
    "linear interpolation",
    "secant",
    "newton-raphson",
    "newton with bracketing",
    "muller"
};

void* const METHODS[NUM_OF_METHODS] = {
    rtbis,
    rtflsp,
    rtsec,
    rtnewt,
    rtsafe,
    muller
};

enum E_METHOD_TYPE
{
    E_NON_DIFF,
    E_DIFF
};

const char METHOD_TYPES[NUM_OF_METHODS] = {
    E_NON_DIFF,
    E_NON_DIFF,
    E_NON_DIFF,
    E_DIFF,
    E_DIFF,
    E_NON_DIFF
};

int main()
{
    int iter1, iter2;
    float root1, root2;
    for (int i = 0; i < NUM_OF_METHODS; ++i)
    {
        printf("METHOD: %s\n", METHOD_NAMES[i]);

        if (METHOD_TYPES[i] == E_NON_DIFF)
        {
            root1 = run(METHODS[i], X_MIN, X_MAX, 1e-4, &iter1);
            root2 = run(METHODS[i], X_MIN, X_MAX, 1e-6, &iter2);
        }
        else
        {
            root1 = run_diff_method(METHODS[i], X_MIN, X_MAX, 1e-4, &iter1);
            root2 = run_diff_method(METHODS[i], X_MIN, X_MAX, 1e-6, &iter2);
        }

        printf("(r.e. 1e-4) root: %.6f n_iter: %d\n", root1, iter1);
        printf("(r.e. 1e-6) root: %.6f n_iter: %d\n", root2, iter2);

        printf("\n\n");
    }
}

float run(float (*solver)(float (*)(float), float, float, float, int*), float x1, float x2, float xacc, int* n_iter)
{
    return solver(f, x1, x2, xacc, n_iter);
}

float run_diff_method(float (*solver)(void (*)(float, float*, float*), float, float, float, int*), float x1, float x2, float xacc, int* n_iter)
{
    return solver(f_df, x1, x2, xacc, n_iter);
}


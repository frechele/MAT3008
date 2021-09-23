#include <stdio.h>
#include "nr.h"
#include "time.h"

#define X_MIN (1.f)
#define X_MAX (10.f)
#define X_ACC (1e-6f)
#define MAX_BRACKETS ((int)1e7)
#define MAX_ROOTS (100)
#define N_TRIALS (1000000)

float muller(float (*f)(float), float x1, float x2, float xacc);

void bessj0_with_gradient(float x, float* y, float *grad)
{
    *y = bessj0(x);
    *grad = -bessj1(x);
}

float run(float (*solver)(float (*)(float), float, float, float), float x1, float x2);
float run_diff_method(float (*solver)(void (*)(float, float*, float*), float, float, float), float x1, float x2);

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
    muller,
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
    // First of all, find root range by bracketing routine.
    float xb1[MAX_ROOTS], xb2[MAX_ROOTS];
    int numOfRoots = MAX_ROOTS;
    zbrak(bessj0, X_MIN, X_MAX, MAX_BRACKETS, xb1, xb2, &numOfRoots);

    clock_t time_begin, time_ela;
    float root;
    for (int i = 0; i < NUM_OF_METHODS; ++i)
    {
        printf("METHOD: %s\n", METHOD_NAMES[i]);

        time_begin = clock();

        for (int j = 1; j <= N_TRIALS; ++j)
        {
            if (METHOD_TYPES[i] == E_NON_DIFF)
            {
                run(METHODS[i], xb1[1], xb2[1]);
            }
            else
            {
                run_diff_method(METHODS[i], xb1[1], xb2[1]);
            }
        }

        time_ela = clock() - time_begin;

        printf("avg. elapsed time: avg. %.5fms", time_ela / (float)N_TRIALS);
        printf("\n\n");
    }
}

float run(float (*solver)(float (*)(float), float, float, float), float x1, float x2)
{
    return solver(bessj0, x1, x2, X_ACC);
}

float run_diff_method(float (*solver)(void (*)(float, float*, float*), float, float, float), float x1, float x2)
{
    return solver(bessj0_with_gradient, x1, x2, X_ACC);
}

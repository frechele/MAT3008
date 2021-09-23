#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "nr.h"

void function1(float x, float* y, float* d)
{
    *y = 10 * exp(-x) * sin(2 * acos(-1) * x) - 2;
    *d = 10 * exp(-x) * (2 * acos(-1) * cos(2 * acos(-1) * x) - sin(2 * acos(-1) * x));
}

void function2(float x, float* y, float* d)
{
    *y = x * x - 2 * x * exp(-x) + exp(-2 * x);
    *d = 2 * exp(-2 * x) * (1 + exp(x)) * (x * exp(x) - 1);
}

void function3(float x, float* y, float* d)
{
    *y = cos(x + sqrt(2)) + x * (x / 2.f + sqrt(2));
    *d = x + sqrt(2) - sin(x + sqrt(2));
}

void function4(float x, float* y, float* d)
{
    *y = powf(sin(x), 2) - x*x + 1;
    *d = 2 * sin(x) * cos(x) - 2 * x;
}

#define N_FUNCTIONS (4)

void* const FUNCTIONS[N_FUNCTIONS] = {
    function1,
    function2,
    function3,
    function4
};

const float FUNCTION_MINS[N_FUNCTIONS] = {
    0.1f,
    0.f,
    -2.f,
    -2.f
};

const float FUNCITON_MAXS[N_FUNCTIONS] = {
    1.f,
    1.f,
    -1.f,
    -1.f
};

#define X_ACC (1e-6f)

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("usage: %s <function id>\n", argv[0]);
        return 1;
    }

    const int functionID = atoi(argv[1]);

    if (functionID < 0 || functionID >= N_FUNCTIONS)
    {
        printf("function id is out of range.\n");
        return 1;
    }

    printf("FUNCTION %d (domain: [%.1f, %.1f])\n", functionID+1, FUNCTION_MINS[functionID], FUNCITON_MAXS[functionID]);

    const float root = rtsafe(FUNCTIONS[functionID], FUNCTION_MINS[functionID], FUNCITON_MAXS[functionID], X_ACC);
    printf("root: %.6f\n", root);
}

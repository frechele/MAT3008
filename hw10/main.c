#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nr.h"

typedef struct {
    float left, right;
} Observation;

struct {
    Observation* X;
    Observation* Y;
    int N;
} data;

int LoadData(const char* filename)
{
    FILE* fp = fopen(filename, "rt");
    if (!fp)
        return 1;

    data.N = 0;
    while (!feof(fp))
    {
        int dump;
        Observation x, y;
        if (fscanf(fp, "%d %f %f %f %f", &dump, &x.left, &x.right, &y.left, &y.right) != 5)
            break;

        data.N++;
        data.X = (Observation*)realloc(data.X, data.N * sizeof(Observation));
        data.Y = (Observation*)realloc(data.Y, data.N * sizeof(Observation));
        data.X[data.N - 1] = x;
        data.Y[data.N - 1] = y;
    }

    data.X = data.X - 1;
    data.Y = data.Y - 1;

    return 0;
}

void FreeData()
{
    free(data.X + 1);
    free(data.Y + 1);
    data.N = 0;
}

float fX(float y)
{
    int i;
    for (i = 1; i <= data.N; ++i)
    {
        if ((data.Y[i].left - y) < 1e-5f)
            break;
    }
    assert(i <= data.N);

    return data.X[i].left;
}

float fY(float x)
{
    int i;
    for (i = 1; i <= data.N; ++i)
    {
        if ((data.X[i].left - x) < 1e-5f)
            break;
    }
    assert(i <= data.N);

    return data.Y[i].left;
}

void xprime(float x, float* a, float* xp, float* dyda, int na)
{
    const float y = fY(x);

    const float denom = a[7] * x + a[8] * y + 1;
    *xp = (a[1] * x + a[2] * y + a[3]) / denom;

    dyda[1] = x / denom;
    dyda[2] = y / denom;
    dyda[3] = 1 / denom;
    dyda[7] = -x * (*xp) / denom;
    dyda[8] = -y * (*xp) / denom;
}

void yprime(float y, float* a, float* yp, float* dyda, int na)
{
    const float x = fX(y);

    const float denom = a[7] * x + a[8] * y + 1;
    *yp = (a[4] * x + a[5] * y + a[6]) / denom;

    dyda[4] = x / denom;
    dyda[5] = y / denom;
    dyda[6] = 1 / denom;
    dyda[7] = -x * (*yp) / denom;
    dyda[8] = -y * (*yp) / denom;
}

int main()
{
    if (LoadData("data/data"))
    {
        printf("Failed to load data\n");
        return 1;
    }
    printf("Load %d observations\n", data.N);

    const int NVAR = 8;

    float* X = vector(1, data.N);
    float* Y = vector(1, data.N);
    float* sig = vector(1, data.N);
    float* a = vector(1, NVAR);
    int* ia = ivector(1, NVAR);
    float** covar = matrix(1, NVAR, 1, NVAR);
    float** alpha = matrix(1, NVAR, 1, NVAR);
    float chisq, alamda;

    for (int i = 1; i <= NVAR; ++i)
        a[i] = 2;

    // 1. Solve for x, x'
    for (int i = 1; i <= data.N; ++i)
    {
        X[i] = data.X[i].left;
        Y[i] = data.X[i].right;
        sig[i] = 1;
    }
    memset(ia, 0, NVAR * sizeof(int));
    ia[1] = ia[2] = ia[3] = ia[7] = ia[8] = 1;
    alamda = -1;
    mrqmin(X, Y, sig, data.N, a, ia, NVAR, covar, alpha, &chisq, xprime, &alamda);

    // 2. Solve for y, y'
    for (int i = 1; i <= data.N; ++i)
    {
        X[i] = data.Y[i].left;
        Y[i] = data.Y[i].right;
        sig[i] = 1;
    }
    memset(ia, 0, NVAR * sizeof(int));
    ia[4] = ia[5] = ia[6] = ia[7] = ia[8] = 1;
    alamda = -1;
    mrqmin(X, Y, sig, data.N, a, ia, NVAR, covar, alpha, &chisq, yprime, &alamda);

    // 3. Print result
    printf("[Result]\n");
    printf("a_11 = %f a_12 = %f a_13 = %f\n", a[1], a[2], a[3]);
    printf("a_21 = %f a_22 = %f a_23 = %f\n", a[4], a[5], a[6]);
    printf("a_31 = %f a_32 = %f\n", a[7], a[8]);

    free_matrix(alpha, 1, NVAR, 1, NVAR);
    free_matrix(covar, 1, NVAR, 1, NVAR);
    free_ivector(ia, 1, NVAR);
    free_vector(a, 1, NVAR);
    free_vector(sig, 1, data.N);
    free_vector(Y, 1, data.N);
    free_vector(X, 1, data.N);

    FreeData();
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nr.h"
#include "lineareq.h"

int runGaussj(LinearEq* eq)
{
    printf("Gauss-Jordan Elimination\n");

    float** b = (float**)malloc(eq->rows * sizeof(float*)) - 1;
    for (int i = 1; i <= eq->rows; ++i)
    {
        b[i] = &eq->b[i] - 1;
    }

    const int result = gaussj(eq->A, eq->rows, b, 1);

    free(b + 1);

    memcpy(eq->x + 1, eq->b + 1, eq->rows * sizeof(float));

    return result;
}

int runLUDecomp(LinearEq* eq)
{
    printf("LU Decomposition\n");

    int* indx = (int*)malloc(eq->rows * sizeof(int)) - 1;
    float d;

    int result = 1;
    if (!(result = ludcmp(eq->A, eq->rows, indx, &d)))
        goto finish;

    lubksb(eq->A, eq->rows, indx, eq->b);
    memcpy(eq->x + 1, eq->b + 1, eq->rows * sizeof(float));

finish:
    free(indx + 1);
    return result;
}

int runSVD(LinearEq* eq)
{
    printf("Singular Value Decomposition\n");

    float* W = CreateVector(eq->cols);
    float** V = CreateMatrix(eq->cols, eq->cols);

    int result = 1;
    if (!(result = svdcmp(eq->A, eq->rows, eq->cols, W, V)))
        goto finish;   

    svbksb(eq->A, W, V, eq->rows, eq->cols, eq->b, eq->x);

finish:
    FreeVector(W);
    FreeMatrix(V, eq->cols);

    return result;
}

void run(int (*solver)(LinearEq*), LinearEq* orig)
{
    LinearEq eq;
    CopyLinearEq(&eq, orig);

    if (solver(&eq))
    {
        printf("[Solution]\n");
        PrintLinearEqSol(&eq);
        printf("\n");
    }
    else
    {
        printf("error occurred\n");
    }

    printf("\n");

    FreeLinearEq(&eq);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <equation num>\n", argv[0]);
        return -1;
    }

    const int eqNum = atoi(argv[1]);
    char eqPath[256];
    sprintf(eqPath, "data/lineq%d.dat", eqNum);

    LinearEq eq;
    LoadLinearEq(eqPath, &eq);
    
    printf("[Equation]\n");
    PrintLinearEq(&eq);
    printf("\n");

    int (*solvers[])(LinearEq*) = {
        runGaussj,
        runLUDecomp,
        runSVD
    };

    for (int i = 0; i < sizeof(solvers) / sizeof(solvers[0]); ++i)
    {
        run(solvers[i], &eq);
    }

    FreeLinearEq(&eq);
}

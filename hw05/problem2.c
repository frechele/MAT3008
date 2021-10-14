#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nr.h"
#include "lineareq.h"

int runMProve(LinearEq* eq)
{
    printf("Iterative Improvement\n");

    int* indx = (int*)malloc(eq->rows * sizeof(int)) - 1;
    float d;

    LinearEq forLUD;
    CopyLinearEq(&forLUD, eq);
    int result = 1;
    if (!(result = ludcmp(forLUD.A, eq->rows, indx, &d)))
        goto finish;

    mprove(eq->A, forLUD.A, eq->rows, indx, eq->b, eq->x);

finish:
    FreeLinearEq(&forLUD);
    free(indx + 1);
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
        runMProve
    };

    for (int i = 0; i < sizeof(solvers) / sizeof(solvers[0]); ++i)
    {
        run(solvers[i], &eq);
    }

    FreeLinearEq(&eq);
}

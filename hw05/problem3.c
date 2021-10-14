#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nr.h"
#include "lineareq.h"

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

    int* indx = (int*)malloc(eq.rows * sizeof(int)) - 1;
    float d;

    if (!ludcmp(eq.A, eq.rows, indx, &d))
        goto finish;

    printf("[Inverse]\n");
    float* col = CreateVector(eq.rows);
    float** y = CreateMatrix(eq.rows, eq.cols);

    for (int j = 1; j <= eq.rows; ++j)
    {
        for (int i = 1; i <= eq.cols; ++i) col[i] = 0;
        col[j] = 1;

        lubksb(eq.A, eq.rows, indx, col);
        for (int i = 1; i <= eq.cols; ++i) y[i][j] = col[i];
    }

    PrintMatrix(y, eq.rows, eq.cols);    

    FreeMatrix(y, eq.rows);
    FreeVector(col);

    printf("[Determinant]\n");
    for (int j = 1; j <= eq.rows; ++j)
        d *= eq.A[j][j];

    printf("%f\n", d);

finish:
    FreeLinearEq(&eq);
}

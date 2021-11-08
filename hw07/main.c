#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "nr.h"

#define MATRIX_SIZE (11)

float** buildMatrix();
void freeMatrix(float** m);
void printMatrix(float** m);

int main()
{
    float** matrix = buildMatrix();
    printf("[Matrix]\n");
    printMatrix(matrix);

    float* d = (float*)malloc(sizeof(float) * MATRIX_SIZE) - 1;
    float** v = buildMatrix();
    int nrot;
    jacobi(matrix, MATRIX_SIZE, d, v, &nrot);
    eigsrt(d, v, MATRIX_SIZE);

    printf("\n[Eigenvalues]\n");
    for (int i = 1; i <= MATRIX_SIZE; ++i)
        printf("%f\t", d[i]);
    
    printf("\n\n[Eigenvectors]\n");
    printMatrix(v);

    free(d + 1);
    freeMatrix(v);
    freeMatrix(matrix);
}

float** buildMatrix()
{
    float** m = (float**)malloc(MATRIX_SIZE * sizeof(float*)) - 1;
    for (int i = 1; i <= MATRIX_SIZE; ++i)
    {
        m[i] = (float*)malloc(MATRIX_SIZE * sizeof(float)) - 1;
    }

    long seed = time(NULL);

    for (int j = 1; j <= MATRIX_SIZE; ++j)
    {
        for (int i = 1; i <= j; ++i)
        {
            m[j][i] = m[i][j] = gasdev(&seed);
        }
    }

    return m;
}

void freeMatrix(float** m)
{
    for (int i = 1; i <= MATRIX_SIZE; ++i)
        free(m[i] + 1);
    free(m + 1);
}

void printMatrix(float** m)
{
    printf("[");
    for (int j = 1; j <= MATRIX_SIZE; ++j)
    {
        printf("[");
        for (int i = 1; i <= MATRIX_SIZE; ++i)
        {
            if (i > 1) printf(", ");
            printf("%8.4f", m[j][i]);
        }
        if (j == MATRIX_SIZE)
            printf("]]\n");
        else
            printf("],\n");
    }
}

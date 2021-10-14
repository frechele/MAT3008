#include "lineareq.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float** CreateMatrix(int rows, int cols)
{
    float** A = (float**)malloc(rows * sizeof(float*)) - 1;

    for (int i = 1; i <= rows; ++i)
    {
        A[i] = (float*)malloc(cols * sizeof(float)) - 1;
    }

    return A;
}

void FreeMatrix(float** A, int rows)
{
    for (int i = 1; i <= rows; ++i)
    {
        free(A[i] + 1);
    }

    free(A + 1);
}

void PrintMatrix(float** A, int rows, int cols)
{
    for (int i = 1; i <= rows; ++i)
    {
        for (int j = 1; j <= cols; ++j)
        {
            printf("%f\t", A[i][j]);
        }
        printf("\n");
    }
}

float* CreateVector(int size)
{
    float* v = (float*)malloc(size * sizeof(float)) - 1;

    return v;
}

void FreeVector(float* v)
{
    free(v + 1);
}

void CreateLinearEq(int rows, int cols, LinearEq* eq)
{
    eq->rows = rows;
    eq->cols = cols;

    eq->A = CreateMatrix(rows, cols);
    assert(eq->A);

    eq->b = CreateVector(rows);
    assert(eq->b);

    eq->x = CreateVector(rows);
    assert(eq->x);
}

void CopyLinearEq(LinearEq* dest, const LinearEq* src)
{
    CreateLinearEq(src->rows, src->cols, dest);

    for (int i = 1; i <= src->rows; ++i)
    {
        memcpy(dest->A[i] + 1, src->A[i] + 1, src->cols * sizeof(float));
    }

    memcpy(dest->b + 1, src->b + 1, src->rows * sizeof(float));
    memcpy(dest->x + 1, src->x + 1, src->rows * sizeof(float));
}

void LoadLinearEq(const char* filename, LinearEq* eq)
{
    FILE* fp = fopen(filename, "rt");
    assert(fp);

    fscanf(fp, "%d %d", &eq->rows, &eq->cols);
    CreateLinearEq(eq->rows, eq->cols, eq);

    for (int i = 1; i <= eq->rows; ++i)
    {
        for (int j = 1; j <= eq->cols; ++j)
        {
            fscanf(fp, "%f", &eq->A[i][j]);
        }
    }

    for (int i = 1; i <= eq->rows; ++i)
    {
        fscanf(fp, "%f", &eq->b[i]);
    }

    fclose(fp);
}

void FreeLinearEq(LinearEq* m)
{
    FreeVector(m->x);
    m->x = NULL;

    FreeVector(m->b);
    m->b = NULL;

    FreeMatrix(m->A, m->rows);
    m->A = NULL;
}

void PrintLinearEq(const LinearEq* m)
{
    printf("shape: %d by %d\n", m->rows, m->cols);
    for (int i = 1; i <= m->rows; ++i)
    {
        for (int j = 1; j <= m->cols; ++j)
        {
            printf("%f\t", m->A[i][j]);
        }
        printf("| %f\n", m->b[i]);
    }
}

void PrintLinearEqSol(const LinearEq* eq)
{
    for (int i = 1; i <= eq->rows; ++i)
    {
        if (i - 1) printf(", ");
        printf("x%d = %f", i, eq->x[i]);
    }
}

void PrintMatrixEq(const LinearEq* eq)
{
    PrintMatrix(eq->A, eq->rows, eq->cols);
}

#ifndef LINEAREQ_H_
#define LINEAREQ_H_

typedef struct
{
    int rows;
    int cols;
    float** A;
    float* b;
    float* x;
} LinearEq;

float** CreateMatrix(int rows, int cols);
void FreeMatrix(float** A, int rows);
void PrintMatrix(float** A, int rows, int cols);
float* CreateVector(int size);
void FreeVector(float* v);

void CreateLinearEq(int rows, int cols, LinearEq* eq);
void CopyLinearEq(LinearEq* dest, const LinearEq* src);
void LoadLinearEq(const char* filename, LinearEq* eq);
void FreeLinearEq(LinearEq* eq);
void PrintLinearEq(const LinearEq* eq);
void PrintLinearEqSol(const LinearEq* eq);
void PrintMatrixEq(const LinearEq* eq);

#endif  // LINEAREQ_H_

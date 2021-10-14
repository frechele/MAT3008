#ifndef NUMERICAL_RECIPES_H_
#define NUMERICAL_RECIPES_H_

extern int gaussj(float** a, int n, float** b, int m);
extern void lubksb(float** a, int n, int* indx, float b[]);
extern int ludcmp(float** a, int n, int* indx, float* d);
extern void svbksb(float** u, float w[], float** v, int m, int n, float b[], float x[]);
extern int svdcmp(float** a, int m, int n, float w[], float** v);

extern void mprove(float** a, float** alud, int n, int indx[], float b[], float x[]);

#endif  // NUMERICAL_RECIPES_H_

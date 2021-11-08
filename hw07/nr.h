#ifndef NUMERICAL_RECIPES_H_
#define NUMERICAL_RECIPES_H_

extern float gasdev(long* idum);
extern float ran1(long* idum);
extern void eigsrt(float d[], float** v, int n);
extern void jacobi(float** a, int n, float d[], float** v, int* nrot);

#endif  // NUMERICAL_RECIPES_H_

#ifndef NUMERICAL_RECIPES_H_
#define NUMERICAL_RECIPES_H_

#include "nr/nrutil.h"

extern void mrqmin(float x[], float y[], float sig[], int ndata, float a[], int ia[],
	int ma, float **covar, float **alpha, float *chisq,
	void (*funcs)(float, float [], float *, float [], int), float *alamda);

#endif  // NUMERICAL_RECIPES_H_

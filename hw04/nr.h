#ifndef NUMERICAL_RECIPES_H_
#define NUMERICAL_RECIPES_H_

extern float rtbis(float (*func)(float), float x1, float x2, float xacc, int* n_iter);
extern float rtflsp(float (*func)(float), float x1, float x2, float xacc, int* n_iter);
extern float rtnewt(void (*funcd)(float, float *, float *), float x1, float x2,
	float xacc, int* n_iter);
extern float rtsafe(void (*funcd)(float, float *, float *), float x1, float x2,
	float xacc, int* n_iter);
extern float rtsec(float (*func)(float), float x1, float x2, float xacc, int* n_iter);

extern void zbrak(float (*fx)(float), float x1, float x2, int n, float xb1[],
	float xb2[], int *nb);

#endif  // NUMERICAL_RECIPES_H_

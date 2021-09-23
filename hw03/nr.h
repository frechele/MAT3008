#ifndef NUMERICAL_RECIPES_H_
#define NUMERICAL_RECIPES_H_

extern float bessj0(float x);
extern float bessj1(float x);

extern float rtbis(float (*func)(float), float x1, float x2, float xacc);
extern float rtflsp(float (*func)(float), float x1, float x2, float xacc);
extern float rtnewt(void (*funcd)(float, float *, float *), float x1, float x2,
	float xacc);
extern float rtsafe(void (*funcd)(float, float *, float *), float x1, float x2,
	float xacc);
extern float rtsec(float (*func)(float), float x1, float x2, float xacc);

extern void zbrak(float (*fx)(float), float x1, float x2, int n, float xb1[],
	float xb2[], int *nb);

#endif  // NUMERICAL_RECIPES_H_

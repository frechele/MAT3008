#include <math.h>
#define MAXIT (30)

#include <stdio.h>

float muller(float (*f)(float), float x1, float x2, float xacc, int* n_iter)
{
    void nrerror(char error_text[]);
    float p0 = (x1 > x2) ? x2 : x1;
    float p1 = (x1 + x2) / 2.f;
    float p2 = (x1 > x2) ? x1 : x2;
    float p3;
    float h0, h1, d0, d1, a, b, c, dx;

    *n_iter = 0;

    for (int j = 0; j < MAXIT; ++j, ++(*n_iter))
    {
        h0 = p1 - p0;
        h1 = p2 - p1;
        d0 = (f(p1) - f(p0)) / (p1 - p0);
        d1 = (f(p2) - f(p1)) / (p2 - p1);

        a = (d1 - d0) / (h1 + h0);
        b = a * h1 + d1;
        c = f(p2);

        dx = (-2 * c) / (b + sqrt(b * b - 4 * a * c) * (b > 0 ? 1 : -1));
        p3 = p2 + dx;

        if (fabs(dx) < p3 * xacc)
            return p3;
        if (isnan(a) || isnan(b) || isnan(c))
            return p2;

        p0 = p1;
        p1 = p2;
        p2 = p3;
    }
    nrerror("Maximum number of iterations exceeded in muller");
    return 0.f;
}

#undef MAXIT

#include <stdio.h>
#include <math.h>

float get_eps_float()
{
    int n;
    float eps;

    for (n = 0; ; ++n)
    {
        if (1 + powf(2.f, -n) == 1)
            break;
    }

    return powf(2.f, -n+1);
}

double get_eps_double()
{
    int n;
    double eps;

    for (n = 0; ; ++n)
    {
        if (1 + pow(2., -n) == 1)
            break;
    }

    return pow(2., -n+1);
}

int main()
{
    printf("[Machine Accuracy by using get_eps]\n");
    printf("Machine Accuracy of float : %g\n", get_eps_float());
    printf("Machine Accuracy of double : %g\n", get_eps_double());
}

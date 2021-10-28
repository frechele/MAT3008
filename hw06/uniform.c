#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "nr.h"

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        printf("Usage: %s <num of samples> <min> <max>\n", argv[0]);
        return 1;
    }

    const long numOfSamples = atol(argv[1]);
    const float a = atof(argv[2]);
    const float b = atof(argv[3]);

    long idum = time(NULL);
    for (int i = 0; i < numOfSamples; ++i)
    {
        printf("%f ", a + (b - a) * ran1(&idum));
    }
}

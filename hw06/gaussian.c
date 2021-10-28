#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "nr.h"

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        printf("Usage: %s <num of samples> <mean> <std>\n", argv[0]);
        return 1;
    }

    const long numOfSamples = atol(argv[1]);
    const float mean = atof(argv[2]);
    const float std = atof(argv[3]);

    long idum = time(NULL);
    for (int i = 0; i < numOfSamples; ++i)
    {
        printf("%f ", (gasdev(&idum) + mean) * std);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include "nr.h"

typedef struct
{
    float x, y, xp, yp;
} Observation;


typedef struct
{
    Observation* obs;
    int N;
} Data;

int LoadData(Data* data, const char* filename)
{
    FILE* fp = fopen(filename, "rt");
    if (!fp)
        return 1;

    data->N = 0;
    while (!feof(fp))
    {
        Observation o;
        if (fscanf(fp, "%f %f %f %f", &o.x, &o.y, &o.xp, &o.yp) != 4)
            break;
        data->N++;
        data->obs = (Observation*)realloc(data->obs, data->N * sizeof(Observation));
        data->obs[data->N - 1] = o;
    }

    data->obs = data->obs - 1;

    return 0;
}

void FreeData(Data* data)
{
    free(data->obs + 1);
    data->N = 0;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    Data data;
    if (LoadData(&data, argv[1]))
    {
        printf("Failed to load data from %s\n", argv[1]);
        return 1;
    }
    printf("Load %d observations\n", data.N);

    float** J = matrix(1, data.N, 1, 3);
    float** y = matrix(1, data.N, 1, 2);
    for (int i = 1; i <= data.N; i++)
    {
        J[i][1] = data.obs[i].x;
        J[i][2] = data.obs[i].y;
        J[i][3] = 1;
        y[i][1] = data.obs[i].xp;
        y[i][2] = data.obs[i].yp;
    }

    float** JJ = matrix(1, 3, 1, 3);
    float** Jy = matrix(1, 3, 1, 2);

    for (int j = 1; j <= 3; ++j)
    {
        for (int i = 1; i <= 3; ++i)
        {
            JJ[i][j] = 0;
            for (int k = 1; k <= data.N; ++k)
            {
                JJ[i][j] += J[k][i] * J[k][j];
            }
        }
    }

    for (int j = 1; j <= 2; ++j)
    {
        for (int i = 1; i <= 3; ++i)
        {
            Jy[i][j] = 0;
            for (int k = 1; k <= data.N; ++k)
            {
                Jy[i][j] += J[k][i] * y[k][j];
            }
        }
    }

    gaussj(JJ, 3, Jy, 2);
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 2; ++j)
            printf("a%d: %f ", j + (i - 1) * 2, Jy[j][i]);

    free_matrix(Jy, 1, 2, 1, 3);
    free_matrix(JJ, 1, 3, 1, 3);

    free_matrix(y, 1, data.N, 1, 2);
    free_matrix(J, 1, data.N, 1, 3);
    FreeData(&data);
}

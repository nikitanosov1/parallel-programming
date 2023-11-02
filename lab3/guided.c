#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

#define CHUNK 10
#define NMAX 3200000
#define Q 28
#define NUM_THREADS 4
#define ITERATION 12

int main()
{
    omp_set_num_threads(NUM_THREADS);
    double *a = (double *)malloc(sizeof(double) * NMAX);
    double *b = (double *)malloc(sizeof(double) * NMAX);
    double *c = (double *)malloc(sizeof(double) * NMAX);

    double s = 0.0;

    int m;
    for (m = 0; m < NMAX; m++)
    {
        a[m] = rand();
        b[m] = rand();
    }

    double st_time, end_time;
    s = 0.0;
    int j;
    int q;
    for (j = 0; j < ITERATION; j++)
    {
        int i;
        st_time = omp_get_wtime();

#pragma omp parallel for schedule(guided, CHUNK) private(i)
        for (i = 0; i < NMAX; i++)
        {
            for (q = 0; q < Q; q++)
                c[i] = a[i] + b[i];
        }

        end_time = omp_get_wtime();
        end_time = end_time - st_time;
        s += end_time;
    }
    printf("GUIDED\nTotal processes = %d with Q = %d", NUM_THREADS, Q);
    printf("\nTIME OF WORK IS %f ", s / ITERATION);
    free(c);
    free(a);
    free(b);
    return 0;
}
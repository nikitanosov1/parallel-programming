#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#define NMAX 3200000
#define Q 28
#define ITERATIONS 12

int main(int argc, char *argv[])
{
	srand(time(0));
	double a[NMAX], b[NMAX], c[NMAX];
	double *a_loc = NULL, *b_loc = NULL, *c_loc = NULL;
	int ProcRank, ProcNum, N = NMAX, i, j, s;
	MPI_Status status;
	double st_time, average_time = 0.0;
	MPI_Init(&argc, &argv);
	for (s = 0; s < ITERATIONS; ++s)
	{
		MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
		MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
		int count = N / ProcNum;
		if (ProcRank == 0)
		{
			for (i = 0; i < N; ++i)
			{
				a[i] = i;
				b[i] = i;
			}
		}
		count = NMAX / ProcNum;
		a_loc = (double *)malloc(count * sizeof(double));
		b_loc = (double *)malloc(count * sizeof(double));
		c_loc = (double *)malloc(count * sizeof(double));

		MPI_Scatter(a, count, MPI_DOUBLE, a_loc, count, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Scatter(b, count, MPI_DOUBLE, b_loc, count, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		if (ProcRank == 0)
		{
			st_time = MPI_Wtime();
		}

		for (i = 0; i < count; ++i)
		{
			for (j = 0; j < Q; ++j)
			{
				c_loc[i] = a_loc[i] + b_loc[i];
			}
		}

		MPI_Gather(c_loc, count, MPI_DOUBLE, c, count, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		if (ProcRank == 0)
			average_time += MPI_Wtime() - st_time;

		free(a_loc);
		free(b_loc);
		free(c_loc);
	}
	if (ProcRank == 0) {
		printf("Total process = %d", ProcNum);
		printf(" with Q = %d", Q);
		printf("\nMPI time of work is %f\n", average_time / ITERATIONS);
	}
	MPI_Finalize();

	return 0;
}

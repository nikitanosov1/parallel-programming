#include "stdlib.h"
#include "stdio.h"
#include "mpi.h"

#define NMAX 3200000
#define ITERATIONS 12
#define Q 28

int main(int argc, char *argv[])
{
    double *a = (double *)malloc(sizeof(double) * NMAX);
    double *b = (double *)malloc(sizeof(double) * NMAX);
    double *c = (double *)malloc(sizeof(double) * NMAX);
    int ProcRank, ProcNum, i;
    MPI_Status Status;
    double st_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    int count = NMAX / ProcNum;
    int remainder = NMAX % ProcNum;

    if (ProcRank == 0)
    {
        for (i = 0; i < NMAX; i++)
        {
            a[i] = rand();
            b[i] = rand();
        }
    }

    double *a_loc = (double *)malloc(sizeof(double) * (count + (ProcRank < remainder ? 1 : 0)));
    double *b_loc = (double *)malloc(sizeof(double) * (count + (ProcRank < remainder ? 1 : 0)));
    double *c_loc = (double *)malloc(sizeof(double) * (count + (ProcRank < remainder ? 1 : 0)));

    st_time = MPI_Wtime();
    int t;
    for (t = 0; t < ITERATIONS; t++)
    {
        int *sendcounts = (int *)malloc(sizeof(int) * ProcNum);
        int *displs = (int *)malloc(sizeof(int) * ProcNum);
        if (ProcRank == 0)
        {
            for (i = 0; i < remainder; i++)
            {
                sendcounts[i] = count + 1;
            }
            for (i = remainder; i < ProcNum; i++)
            {
                sendcounts[i] = count;
            }
            displs[0] = 0;
            for (i = 1; i < ProcNum; i++)
            {
                displs[i] = displs[i - 1] + sendcounts[i - 1];
            }
        }

        MPI_Scatterv(a, sendcounts, displs, MPI_INT, a_loc, count + (ProcRank < remainder ? 1 : 0), MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatterv(b, sendcounts, displs, MPI_INT, b_loc, count + (ProcRank < remainder ? 1 : 0), MPI_INT, 0, MPI_COMM_WORLD);

        for (i = 0; i < count + (ProcRank < remainder ? 1 : 0); i++)
        {
            c_loc[i] = 0;
            int q;
            for (q = 0; q < Q; q++)
            {
                c_loc[i] += a_loc[i] + b_loc[i];
            }
        }

        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Gatherv(c_loc, count + (ProcRank < remainder ? 1 : 0), MPI_INT, c, sendcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

        free(sendcounts);
        free(displs);
    }
    end_time = MPI_Wtime();

    if (ProcRank == 0)
    {
        printf("MPI");
        printf("\nTotal process = % d with Q = % d and amount of elements = % d", ProcNum, Q, NMAX);
        printf("\nTIME OF WORK IS % f", (end_time - st_time) / ITERATIONS);
    }
    free(a);
    free(b);
    free(c);
    free(a_loc);
    free(b_loc);
    free(c_loc);
    MPI_Finalize();
    return 0;
}

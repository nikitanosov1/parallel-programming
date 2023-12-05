#include "mpi.h"
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define ROWS_A 4
#define COLS_A 2
#define ROWS_B COLS_A
#define COLS_B 3

void printMatrix(int* matrix, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		printf("\n");
		for (int j = 0; j < cols; ++j) {
			printf("%d  ", matrix[i * cols + j]);
		}
	}
	printf("\n");
}

int main(int argc, char* argv[]) { 
	MPI_Status Status;
	int ProcRank, ProcNum;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	MPI_Request request;
	int *blockA, *blockB, *blockC, *A, *B, *C;
	double startTime, endTime;

	blockA = (int*)malloc(ROWS_A / ProcNum * COLS_A * sizeof(int));
	blockB = (int*)malloc(ROWS_B / ProcNum * COLS_B * sizeof(int));
	blockC = (int*)malloc(ROWS_A / ProcNum * COLS_B * sizeof(int));
	for (int i = 0; i < ROWS_A / ProcNum * COLS_B; ++i) {
		blockC[i] = 0;
	}

	if (ProcRank == 0) {
		A = (int*)malloc(ROWS_A * COLS_A * sizeof(int));
		B = (int*)malloc(ROWS_B * COLS_B * sizeof(int));
		C = (int*)malloc(ROWS_A * COLS_B * sizeof(int));
		for (int i = 0; i < ROWS_A * COLS_A; ++i) {
			A[i] = 1;
		}
		for (int i = 0; i < ROWS_B * COLS_B; ++i) {
			B[i] = 2;
		}
	}
	int blockSizeA = ROWS_A / ProcNum * COLS_A;
	int blockSizeB = ROWS_B / ProcNum * COLS_B;
	int rowCountInBlockA = ROWS_A / ProcNum;
	int rowCountInBlockB = ROWS_B / ProcNum;
	startTime = MPI_Wtime();
	MPI_Scatter(A, blockSizeA, MPI_INT, blockA, blockSizeA, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(B, blockSizeB, MPI_INT, blockB, blockSizeB, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < ProcNum; ++i) {
		for (int blockCRowIndex = 0; blockCRowIndex < rowCountInBlockA; ++blockCRowIndex) {
			for (int blockCColIndex = 0; blockCColIndex < COLS_B; ++blockCColIndex) {
				for (int k = 0; k < rowCountInBlockB; ++k) {
					int startColInA = (i + ProcRank) % ProcNum * rowCountInBlockB;
					blockC[COLS_B * blockCRowIndex + blockCColIndex] += blockA[COLS_A * blockCRowIndex + startColInA + k] * blockB[COLS_B * k + blockCColIndex];
				}
			}
		}
		MPI_Isend(blockB, blockSizeB, MPI_INT, (ProcRank + 1) % ProcNum, 0, MPI_COMM_WORLD, &request);
		MPI_Recv(blockB, blockSizeB, MPI_INT, (ProcNum + ProcRank - 1) % ProcNum, 0, MPI_COMM_WORLD, &Status);
	}	
	MPI_Gather(blockC, ROWS_A / ProcNum * COLS_B, MPI_INT, C, ROWS_A / ProcNum * COLS_B, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	
	endTime = MPI_Wtime();
	double total_time = endTime - startTime;
	if (ProcRank == 0) {
		printf("\nTime of work is %f", total_time);
		printMatrix(C, ROWS_A, COLS_B);
		free(A);
		free(B);
		free(C);
	}
	free(blockA);
	free(blockB);
	free(blockC);
	MPI_Finalize();
	return 0;
}

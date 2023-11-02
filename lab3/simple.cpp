#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_SIZE 3200000
#define ITERATION 12
#define Q 28

int main(int argc, char* argv[]) {
    int i, j, count;
    double sum, total_time = 0;
    double* a = new double[N_SIZE];
    double* b = new double[N_SIZE];
    double* c = new double[N_SIZE];
    for (i = 0; i < N_SIZE; ++i) {
        a[i] = 1;
        b[i] = 1;
    }

    clock_t start_time, end_time;

    // Последовательное суммирование
    for (count = 0; count < ITERATION; count++) {
        start_time = clock();
        for (i = 0; i < N_SIZE; i++) {
            for (j = 0; j < Q; ++j) {
                c[i] = a[i] + b[i];
            }
        }
        end_time = clock();
        end_time = end_time - start_time;
        total_time += end_time;
    }

    sum = sum / (ITERATION * Q);
    printf("\nConsistent Q: %d", Q);
    printf("\nTotal Sum = %10.2f", sum);
    printf("\nTIME OF WORK IS %f ", total_time / CLOCKS_PER_SEC / ITERATION);

    return 0;
}
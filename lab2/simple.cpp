#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_SIZE 3200000

int main(int argc, char* argv[]) {
    int i, j, num_iterations = 12, count, Q = 28;
    double sum, total_time = 0;
    double* a = new double[N_SIZE];
    for (i = 0; i < N_SIZE; ++i) {
        a[i] = 1;
    }

    clock_t start_time, end_time;

    sum = 0;
    // Последовательное суммирование
    for (count = 0; count < num_iterations; count++) {
        start_time = clock();
        for (i = 0; i < N_SIZE; i++) {
            for (j = 0; j < Q; ++j) {
                sum += a[i];
            }
        }
        end_time = clock();
        end_time = end_time - start_time;
        total_time += end_time;
    }

    sum = sum / (num_iterations * Q);
    printf("\nConsistent Q: %d", Q);
    printf("\nTotal Sum = %10.2f", sum);
    printf("\nTIME OF WORK IS %f ", total_time / CLOCKS_PER_SEC / num_iterations);

    sum = 0;
    total_time = 0;

    return 0;
}
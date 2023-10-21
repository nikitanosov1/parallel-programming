#include <math.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    omp_set_num_threads(4); // Менять на [4, 8, 16]
    int N = 3200000;
    int i, j, Q = 28;
    double sum = 0, total_time = 0;
    double* a = new double[N];
    for (i = 0; i < N; ++i) {
        a[i] = 1;
    }
    double st_time, end_time;
    //reduction
    st_time = omp_get_wtime();
#pragma omp parallel for shared(a) private(i, j) reduction(+: sum)
    for (i = 0; i < N; i++) {
        for (j = 0; j < Q; ++j) {
            sum += a[i];
        }
    }
    end_time = omp_get_wtime();
    end_time = end_time - st_time;
    total_time = end_time;
    sum = sum / Q;
    printf("\n\nReduction Q: %d", Q);
    printf("\nTotal Sum = %10.2f", sum);
    printf("\nTIME OF WORK IS %f ", total_time);

    sum = 0;
    total_time = 0;
    //atomic
    st_time = omp_get_wtime();
#pragma omp parallel for shared(a) private(i, j)
    for (i = 0; i < N; i++) {

        for (j = 0; j < Q; ++j) {
#pragma omp atomic
            sum += a[i];
        }
    }
    end_time = omp_get_wtime();
    end_time = end_time - st_time;
    total_time = end_time;
    sum = sum / Q;
    printf("\n\nAtomic Q: %d", Q);
    printf("\nTotal Sum = %10.2f", sum);
    printf("\nTIME OF WORK IS %f ", total_time);
    sum = 0;
    total_time = 0;

    //critical
    st_time = omp_get_wtime();
#pragma omp parallel for shared(a) private(i, j)
    for (i = 0; i < N; i++) {
        for (j = 0; j < Q; ++j) {
#pragma omp critical
            sum += a[i];
        }
    }
    end_time = omp_get_wtime();
    end_time = end_time - st_time;
    total_time = end_time;
    sum = sum / Q;
    printf("\n\nCritical Q: %d", Q);
    printf("\nTotal Sum = %10.2f", sum);
    printf("\nTIME OF WORK IS %f ", total_time);
    delete a;
    system("pause");
    return 0;
}
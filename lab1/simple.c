#include <omp.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    double result_time = 0;
    double start_time = omp_get_wtime();
    for (int i = 0; i < 6; ++i)
    {

    printf("Hello World %d \n", i);

    }
    double finish_time = omp_get_wtime();
    result_time += finish_time - start_time;
    printf("Result time = %.32f\n", result_time);

    return 0;
}
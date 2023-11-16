#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NMAX 3200000 // 3200000 800000 400000
#define ITERATIONS 12

int main(int argc, char* argv[]) {
	int i, j;
    double a[NMAX], b[NMAX], sum[NMAX];
	double start_time, end_time;

	//заполнение массива
	for (i = 0; i < NMAX; ++i) {
		a[i] = rand();
		b[i] = rand();
	}

	start_time = clock();
	for (j = 0; j < ITERATIONS; ++j) {
		for (i = 0; i < NMAX; ++i) {
			sum[i] = a[i] + b[i];
		}
	}
	end_time = clock();

	printf("\nLinear with N = %d", NMAX);
	printf("\nLINEAR TIME OF WORK IS %f", (end_time - start_time) / CLOCKS_PER_SEC / ITERATIONS);

	return 0;
}

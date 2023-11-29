#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define ROWS_A 2048
#define COLS_A 2048
#define ROWS_B COLS_A
#define COLS_B 2048

using namespace std;

int main(int argc, char* argv[]) {
    int** A = new int*[ROWS_A];
    for (int i = 0; i < ROWS_A; ++i) {
        A[i] = new int[COLS_A];
        for (int j = 0; j < COLS_A; ++j) {
            A[i][j] = 1;
        }
    }

    int** B = new int*[ROWS_B];
    for (int i = 0; i < ROWS_B; ++i) {
        B[i] = new int[COLS_B];
        for (int j = 0; j < COLS_B; ++j) {
            B[i][j] = 2;
        }
    }

    int** C = new int*[ROWS_A];
    for (int i = 0; i < ROWS_A; ++i) {
        C[i] = new int[COLS_B];
        for (int j = 0; j < COLS_B; ++j) {
            C[i][j] = 0;
        }
    }

    clock_t start_time = clock();

    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            for (int k = 0; k < ROWS_B; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    clock_t end_time = clock();
    double total_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    cout << "Time of work is " << total_time << " seconds" << endl;

    // for (int i = 0; i < ROWS_A; ++i) {
    //     for (int j = 0; j < COLS_B; ++j) {
    //         cout << C[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < ROWS_A; ++i) {
        delete[] A[i];
    }
    delete[] A;

    for (int i = 0; i < ROWS_B; ++i) {
        delete[] B[i];
    }
    delete[] B;

    for (int i = 0; i < ROWS_A; ++i) {
        delete[] C[i];
    }

    delete[] C;

    return 0;
}
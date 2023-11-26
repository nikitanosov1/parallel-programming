#include <mpi.h>
#include <iostream>

#define MATRIX_SIZE 4 // Размерность матриц

// Функция для умножения матриц
void multiply_matrices(int* submatrix_A, int* matrix_B, int* submatrix_C, int block_size) {
    for (int i = 0; i < block_size; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            submatrix_C[i * MATRIX_SIZE + j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                submatrix_C[i * MATRIX_SIZE + j] += submatrix_A[i * MATRIX_SIZE + k] * matrix_B[k * MATRIX_SIZE + j];
            }
        }
    }
}

int main(int argc, char** argv) {
    int rank, size;
    int* matrix_A = nullptr;
    int* matrix_B = nullptr;
    int* submatrix_A = nullptr;
    int* submatrix_C = nullptr;
    int block_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Инициализация матрицы А только на процессе с рангом 0
    if (rank == 0) {
        matrix_A = new int[MATRIX_SIZE * MATRIX_SIZE];
        for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; i++) {
            matrix_A[i] = 1;
        }
    }

    matrix_B = new int[MATRIX_SIZE * MATRIX_SIZE];
    // Инициализация матрицы B на всех процессах
    if (rank == 0) {
        for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; i++) {
            matrix_B[i] = 2;
        }
    }
    MPI_Bcast(matrix_B, MATRIX_SIZE * MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Расчет размера блока для каждого процесса
    block_size = MATRIX_SIZE / size; 

    // Выделение памяти для блока матрицы А и матрицы С
    submatrix_A = new int[block_size * MATRIX_SIZE];
    submatrix_C = new int[block_size * MATRIX_SIZE];

    // Рассылка блоков матрицы А на все процессы
    MPI_Scatter(matrix_A, block_size * MATRIX_SIZE, MPI_INT, submatrix_A, block_size * MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Рассылка матрицы B на все процессы
    // MPI_Bcast(matrix_B, MATRIX_SIZE * MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Умножение блоков матрицы А на матрицу B
    multiply_matrices(submatrix_A, matrix_B, submatrix_C, block_size);

    // Сбор результатов с каждого процесса на процессе с рангом 0
    MPI_Gather(submatrix_C, block_size * MATRIX_SIZE, MPI_INT, matrix_A, block_size * MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Вывод результата на процессе с рангом 0
    if (rank == 0) {
        std::cout << "Matrix C:" << std::endl;
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                std::cout << matrix_A[i * MATRIX_SIZE + j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Освобождение памяти
    delete[] matrix_A;
    delete[] matrix_B;
    delete[] submatrix_A;
    delete[] submatrix_C;

    // MPI_Type_free(&block_type);
    MPI_Finalize();

    return 0;
}
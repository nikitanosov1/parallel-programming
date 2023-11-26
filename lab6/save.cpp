#include <iostream>
#include <mpi.h>

#define N 4 // размерность матриц

// Функция для блочно-строчного умножения матриц
void block_matrix_multiplication(int *a, int *b, int *c, int block_size, int num_procs, int my_rank) {
    int *buffer = new int[N * block_size]; // буфер для промежуточных результатов
    int *recv_buffer = new int[N * block_size]; // буфер для приема данных
    int *temp_buffer = new int[block_size]; // буфер для временных данных

    // Инициализация буфера
    for (int i = 0; i < N * block_size; i++) {
        buffer[i] = 0;
        recv_buffer[i] = 0;
    }

    // Умножение блоков матриц
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < block_size; i++) {
            for (int j = 0; j < block_size; j++) {
                buffer[i * N + j] += a[i * N + k] * b[k * N + j];
            }
        }
    }

    // Сбор результатов
    MPI_Reduce(buffer, recv_buffer, N * block_size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Отправка результатов
    if (my_rank == 0) {
        for (int i = 0; i < num_procs; i++) {
            if (i != 0) {
                MPI_Recv(temp_buffer, block_size, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (int j = 0; j < block_size; j++) {
                    recv_buffer[(i * block_size + j) * N] = temp_buffer[j];
                }
            }
        }
    } else {
        MPI_Send(buffer, block_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Вывод результатов
    if (my_rank == 0) {
        std::cout << "Результат умножения матриц:" << std::endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << recv_buffer[i * N + j] << " ";
            }
            std::cout << std::endl;
        }
    }

    delete[] buffer;
    delete[] recv_buffer;
    delete[] temp_buffer;
}

int main(int argc, char **argv) {
    int num_procs, my_rank, block_size;

    // Инициализация MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Вычисление размера блока
    block_size = N / num_procs;

    // Выделение памяти для блоков матриц
    int *a = new int[block_size * N];
    int *b = new int[block_size * N];
    int *c = new int[block_size * N];

    // Инициализация блоков матриц
    for (int i = 0; i < block_size; i++) {
        for (int j = 0; j < N; j++) {
            // a[i * N + j] = my_rank * block_size + i + 1;
            // b[i * N + j] = my_rank * block_size + i + j + 1;
            // c[i * N + j] = 0;
            a[i * N + j] = 1;
            b[i * N + j] = 2;
            c[i * N + j] = 0;
        }
    }

    // Вызов функции блочно-строчного умножения матриц
    block_matrix_multiplication(a, b, c, block_size, num_procs, my_rank);

    // Освобождение памяти
    delete[] a;
    delete[] b;
    delete[] c;

    // Завершение MPI
    MPI_Finalize();

    return 0;
}
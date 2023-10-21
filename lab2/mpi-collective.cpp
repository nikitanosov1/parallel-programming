#include "mpi.h"
#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[]) {
    double* b, TotalSum, ProcSum = 0.0; // Объявление переменных для хранения суммы
    double* a;
    int ProcRank, ProcNum, N = 3200000, i, j, Q = 28, k;
    double st_time, end_time;
    MPI_Init(&argc, &argv); // Инициализация MPI
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum); // Получение количества процессов
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank); // Получение номера текущего процесса
    if (ProcRank == 0) {
        a = static_cast<double*>(malloc(N * sizeof(double))); // Выделение памяти для массива a на процессе 0
        for (i = 0; i < N; ++i) {
            a[i] = 1; // Инициализация массива a на процессе 0
        }
    }
    st_time = MPI_Wtime(); // Запись текущего времени
    b = static_cast<double*>(malloc((N / ProcNum) * sizeof(double))); // Выделение памяти для массива b на каждом процессе
    MPI_Scatter(a, N / ProcNum, MPI_DOUBLE, b, N / ProcNum, MPI_DOUBLE, 0, MPI_COMM_WORLD); // Разделение массива a между всеми процессами
    if (ProcRank == 0) {
        free(a); // Освобождение памяти массива a на процессе 0
    }
    
    k = N / ProcNum;
    for (i = 0; i < k; ++i) {
        for (j = 0; j < Q; ++j) {
            ProcSum = ProcSum + b[i]; // Вычисление суммы элементов массива b на каждом процессе
        }
    }
    ProcSum /= (double)Q; // Деление суммы на Q
    MPI_Reduce(&ProcSum, &TotalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); // Сбор суммы со всех процессов на процессе 0
    end_time = MPI_Wtime(); // Запись текущего времени
    end_time = end_time - st_time; // Вычисление времени выполнения
    if (ProcRank == 0) {
        printf(" Sum = %10.2f", TotalSum); // Вывод общей суммы на процессе 0
        printf("\n Time = %f \n", end_time); // Вывод времени выполнения на процессе 0
    }
    free(b); // Освобождение памяти массива b на каждом процессе
    MPI_Finalize(); // Завершение работы MPI
    return 0;
}

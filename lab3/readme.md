# С чего начать?

С помощью программы WinSCP зайти на кластер Королева (sk.ssau.ru), перетащить все cpp файлы сюда и два вспомогательных файла с расширением .sl
![Alt text](image.png)

Также в терминале Королева нужно установить модули, прописав

module load intel/icc18

module load intel/mpi4

Далее, нажав сюда, мы подключимся к Королеву через Putty
![Alt text](image-1.png)

## MPI

Для компиляции mpi программы
mpicc -o mpi mpi.cpp

Для запуска mpi программы

1. Поменять числа в Script_mpi.sl в строке #SBATCH --nodes=1 --ntasks-per-node=4
2. Выполнить sbatch Script_mpi.sl

## OpenMP

Для компиляции openmp программы
icc -fopenmp -o openmp openmp.cpp

Для запуска openmp программы
Выполнить sbatch Script_openmp.sl

# Полезные строчки

icc -fopenmp -o openmp dynamic.c
icc -fopenmp -o openmp guided.c
icc -fopenmp -o openmp static.c
mpicc -o mpi mpi.c
g++ -o simple simple.cpp
./simple

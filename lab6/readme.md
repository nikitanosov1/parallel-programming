# Доп ЛР #6

Условие:
![Alt text](image.png)

Часть теории взята [из методички Д.Л. Головашкина](http://repo.ssau.ru/bitstream/Uchebnye-izdaniya/Parallelnye-algoritmy-vychislitelnoi-lineinoialgebry-Elektronnyi-resurs-ucheb-posobie-80351/1/Головашкин%20Д.Л.%20Параллельные%20алгоритмы%20вычислительной%20линейной%20алгебры%202019.pdf)

Лабораторная работа реализована на топологии "процессорное кольцо" с помощью MPI на C++

## Запуск

- Скомпилировать mpi программу (Этот процесс описан в предыдущих лабах)
- Запустить mpiexec -n {кол-во процессов} ./mpi.exe

Пример:
mpiexec -n 2 ./mpi.exe

## Запуск последовательной программы

g++ -o simple simple.cpp

./simple

PS. Проверь еще, что в vscode стоит g++, а не gcc. Ты же на плюсах пишешь, а не на си.

MPI на суперкомпьютере:

```
module load intel/icc18
module load intel/mpi4
mpicc -o mpi mpi.cpp
sbatch Script_mpi.sl
```

Последовательная на суперкомпьютере:

```
g++ -o simple simple.cpp
sbatch simple.sl
```

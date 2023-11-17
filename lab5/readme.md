Последовательная (git bash)
g++ -o simple simple.cpp
./simple

Запуск обычной CUDA
nvcc cuda.cu

Запуск CUDA вместе с библиотекой cuBLAS
nvcc cuda.cu -lcublas -dlink -o cuda
nvcc cuda.cu -lcublas -dlink -lcublas_device -lcudadevrt

На суперкомпьютере
sbatch cuda.sl

g++ -o simple simple.cpp
sbatch simple.sl

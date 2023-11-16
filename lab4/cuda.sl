#!/bin/bash

#SBATCH --job-name=myjob_gpu
#SBATCH --nodes=1
#SBATCH --gres=gpu
#SBATCH --time=00:05:00


module load cuda/8.0
nvcc -g -G -O0 -DGRID_SIZE=1024 -DBLOCK_SIZE=128 -DNMAX=3200000 –DITERATIONS=12 -lcublas -o cuda.bin cuda.cu
./cuda.bin
 

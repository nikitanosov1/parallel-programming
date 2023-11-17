#!/bin/bash

#SBATCH --job-name=myjob
#SBATCH --nodes=1
#SBATCH --gres=gpu
#SBATCH --time=00:05:00

module load cuda/8.0
nvcc -g -G -O0 -lcublas -lcurand -o cuda.bin cuda.cu

./cuda.bin

#!/bin/bash
#SBATCH --job-name=myjob
#SBATCH --time=00:10:00
#SBATCH --nodes=1 --ntasks-per-node=4
#SBATCH --mem=1gb

./openmp
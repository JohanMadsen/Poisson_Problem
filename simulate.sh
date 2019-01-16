#!/bin/bash

# Setup for batch stuff
#BSUB -J POISSON
#BSUB -o poisson_sim%J.out
#BSUB -q hpcintro
#BSUB -W 60
#BSUB -n 1
#BSUB -R "rusage[mem=8GB]"
module load gcc/8.2.0

# Put environment variables in here and call poisson.gcc
#export OMP_NUM_THREADS=2
#export OMP_SCHEDULE=
#export OMP_WAIT_POLICY=

mkdir -p sim
rm -r sim/seq_jacobi.txt
rm -r sim/seq_gauss.txt

for i in {1..24}
do
	./poisson.gcc jacobi $(($i*100)) 1000000000 0.1 >> sim/seq_jacobi.txt
	./poisson.gcc gauss $(($i*100)) 1000000000 0.1 >> sim/seq_gauss.txt
done

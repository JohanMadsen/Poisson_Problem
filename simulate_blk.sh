#!/bin/bash

# Setup for batch stuff
#BSUB -J POISSON
#BSUB -o poisson_sim%J.out
#BSUB -q hpcintro
#BSUB -W 15
#BSUB -n 24 -R "span[hosts=1]"
#BSUB -R "rusage[mem=0.5GB]"
module load gcc/8.2.0

# Put environment variables in here and call poisson.gcc
export OMP_SCHEDULE=static
export OMP_WAIT_POLICY=active
export OMP_PROC_BIND=true

mkdir -p sim
rm -r sim/simple_par_jacobi_advanced*.txt

for i in {20..24}
do
	export OMP_NUM_THREADS=12
    ./poisson.gcc jacobi $(($i*100)) 2000 0.0 >> sim/simple_par_jacobi_advanced_12.txt
	export OMP_NUM_THREADS=16
    ./poisson.gcc jacobi $(($i*100)) 2000 0.0 >> sim/simple_par_jacobi_advanced_16.txt
	export OMP_NUM_THREADS=20
    ./poisson.gcc jacobi $(($i*100)) 2000 0.0 >> sim/simple_par_jacobi_advanced_20.txt
	export OMP_NUM_THREADS=24
    ./poisson.gcc jacobi $(($i*100)) 2000 0.0 >> sim/simple_par_jacobi_advanced_24.txt
done

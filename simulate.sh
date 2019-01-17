#!/bin/bash

# Setup for batch stuff
#BSUB -J POISSON
#BSUB -o poisson_sim%J.out
#BSUB -q hpcintro
#BSUB -W 120
#BSUB -n 16 -R "span[hosts=1]"
#BSUB -R "rusage[mem=16GB]"
module load gcc/8.2.0

# Put environment variables in here and call poisson.gcc
#export OMP_SCHEDULE=
#export OMP_WAIT_POLICY=

mkdir -p sim
rm -r sim/par_jacobi_advanced*.txt

for i in {1..16}
do
	export OMP_NUM_THREADS=1
	./poisson.gcc jacobi $(($i*50)) 20000 0.0 >> sim/par_jacobi_advanced_1.txt
	export OMP_NUM_THREADS=2
    ./poisson.gcc jacobi $(($i*50)) 20000 0.0 >> sim/par_jacobi_advanced_2.txt
    export OMP_NUM_THREADS=4
    ./poisson.gcc jacobi $(($i*50)) 20000 0.0 >> sim/par_jacobi_advanced_4.txt
    export OMP_NUM_THREADS=8
	./poisson.gcc jacobi $(($i*50)) 20000 0.0 >> sim/par_jacobi_advanced_8.txt
	export OMP_NUM_THREADS=12
    ./poisson.gcc jacobi $(($i*50)) 20000 0.0 >> sim/par_jacobi_advanced_12.txt
	export OMP_NUM_THREADS=16
    ./poisson.gcc jacobi $(($i*50)) 20000 0.0 >> sim/par_jacobi_advanced_16.txt
done

for i in {9..24}
do
	export OMP_NUM_THREADS=1
	./poisson.gcc jacobi $(($i*100)) 20000 0.0 >> sim/par_jacobi_advanced_1.txt
	export OMP_NUM_THREADS=2
    ./poisson.gcc jacobi $(($i*100)) 20000 0.0 >> sim/par_jacobi_advanced_2.txt
    export OMP_NUM_THREADS=4
    ./poisson.gcc jacobi $(($i*100)) 20000 0.0 >> sim/par_jacobi_advanced_4.txt
    export OMP_NUM_THREADS=8
	./poisson.gcc jacobi $(($i*100)) 20000 0.0 >> sim/par_jacobi_advanced_8.txt
	export OMP_NUM_THREADS=12
    ./poisson.gcc jacobi $(($i*100)) 20000 0.0 >> sim/par_jacobi_advanced_12.txt
	export OMP_NUM_THREADS=16
    ./poisson.gcc jacobi $(($i*100)) 20000 0.0 >> sim/par_jacobi_advanced_16.txt
done

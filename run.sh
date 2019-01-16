# Setup for batch stuff
#BSUB -J POISSON
#BSUB -o poisson_sim%J.out
#BSUB -q hpcintro
#BSUB -W 5
#BSUB -R "rusage[mem=8GB]"
module load gcc/8.2.0

# Put environment variables in here and call main.gcc
export OMP_NUM_THREADS=2
export OMP_SCHEDULE=
export OMP_WAIT_POLICY=
./main.gcc 64 10000 0.1
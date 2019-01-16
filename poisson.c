#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "iterator.h"
#include "init.h"
#include "datatools.h"


int jacobi(int N, int kmax, double threshold, double ***u, double ***f, int bs) {
    double **uold = malloc_2d(N + 2, N + 2);
    for (int i = 0; i < N + 2; ++i) {
        for (int j = 0; j < N + 2; ++j) {
            uold[i][j] = (*u)[i][j];
        }
    }
    double d = DBL_MAX;
    int k = 0;
    while (d > threshold && k < kmax) {
        swap(u, &uold);
        d = jacobiIteration(u, &uold, f, N);
        k += 1;
    }
    free_2d(uold);
    return k;
}

int gauss(int N, int kmax, double threshold, double ***u, double ***f, int bs) {
    double d = DBL_MAX;
    int k = 0;
    while (d > threshold && k < kmax) {
        d = gaussIteration(u, f, N);
        k += 1;
    }
    return k;
}

int main(int argc, char *argv[]) {
    int N;
    int kmax;
    double threshold;
    char *funcType;
    int bs;
    double mflops, memory;
    long ts, te;
    struct timeval timecheck;
    int iterations;

    N = 512;
    kmax = 10000;
    threshold = 0.1;
    funcType = "jacobi";
    bs = 16;

    // command line arguments for the three sizes above
    if (argc >= 2)
        funcType = argv[1];

    if (argc >= 3)
        N = atoi(argv[2]);

    if (argc >= 4)
        kmax = atoi(argv[3]);

    if (argc >= 5)
        threshold = atof(argv[4]);

    if (argc >= 6) {
        bs = atoi(argv[5]);
    }

    double gridspacing = (double) 2 / (N + 1);
    double **f = generateF(N, gridspacing);
    double **u = generateU(N);
    // Initializing time
    gettimeofday(&timecheck, NULL);
    ts = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;

    if (strcmp(funcType, "jacobi") == 0) {
        memory = ((N+2) * (N+2) * 2 + (N*N)) * sizeof(double);
        iterations = jacobi(N, kmax, threshold, &u, &f, bs);
    } else if (strcmp(funcType, "gauss") == 0) {
        memory = ((N+2) * (N+2) + (N*N)) * sizeof(double);
        iterations = gauss(N, kmax, threshold, &u, &f, bs);
    } else {
        printf("First parameter should be either jacobi or gauss");
        exit(1);

    }
    // Get elapsed time
    gettimeofday(&timecheck, NULL);
    te = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
    long elapsed = (te - ts) / 1000;

    mflops = 1.0e-06 * iterations * (N * N * FLOP + 4); // +4 is for sqrt
    mflops /= elapsed;
    memory /= 1024.0; // KB


    printf("%f\t", mflops); // MFLOP/S
    printf("%.3f\t", (double) elapsed); // Time spent
    printf("%f\t", memory); // Mem footprint
    printf("%d\t", iterations); // iterations
    printf("%d\n", N); // N
    //print_matrix(u, N + 2);
    return 0;
}

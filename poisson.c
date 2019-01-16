#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include "iterator.h"
#include "init.h"
#include "datatools.h"

void jacobi(int N, int kmax, double threshold, double ***u, double ***f, double gridspacingsqr) {
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
        d = jacobiIteration(u, &uold, f, gridspacingsqr, N);
        k += 1;
    }
    printf("%d  ", k);
    free_2d(uold);
}

void gauss(int N, int kmax, double threshold, double ***u, double ***f, double gridspacingsqr) {
    double d = DBL_MAX;
    int k = 0;
    while (d > threshold && k < kmax) {
        d = gaussIteration(u, f, gridspacingsqr, N);
        k += 1;
    }
    printf("%d  ", k);
}

int main(int argc, char *argv[]) {
    int N = 8;
    int kmax = 10000;
    double threshold = 0.1;

    // command line arguments for the three sizes above
    if (argc == 4) {
        N = atoi(argv[1]);
        kmax = atoi(argv[2]);
        threshold = atof(argv[3]);
    }

    double gridspacing = (double) 2 / (N + 1);
    double **f = generateF(N, gridspacing);
    double **u = generateU(N);

    jacobi(N, kmax, threshold, &u, &f, gridspacing * gridspacing);
    print_matrix(u, N + 2);
    gauss(N, kmax, threshold, &u, &f, gridspacing * gridspacing);
    print_matrix(u, N + 2);
    return 0;
}

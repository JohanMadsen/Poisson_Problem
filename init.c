#include "init.h"
#include "datatools.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))


double **generateF(int N, double gridspacing) {
    double **f = malloc_2d(N, N);
    double constant = gridspacing * gridspacing * 200;
    int i, j;
#pragma  omp parallel for private(i, j) schedule(static)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            f[i][j] = 0;
            if (gridspacing * j >= 1 && gridspacing * j <= 1 + 1.0 / 3 && gridspacing * i >= 1.0 / 3 &&
                gridspacing * i <= 2.0 / 3) {
                f[i][j] = constant;
            }
        }
    }

    return f;
}

double **generateU(int N) {
    double **u = malloc_2d(N + 2, N + 2);
    int i, j;
#pragma  omp parallel for private(i, j) schedule(static)
    for (i = 0; i < N + 2; ++i) {
        for (j = 0; j < N + 2; ++j) {
            u[i][j] = (j == 0 || j == N + 1 || i == N + 1) ? 20.0 : 0.0;
        }
    }

    return u;
}

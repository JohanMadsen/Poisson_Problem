#include "init.h"
#include "datatools.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))


double **generateF(int N, double gridspacing, int bs) {
    double **f = malloc_2d(N, N);
    double constant = gridspacing * gridspacing * 200;
    int i1, j1, i, j;
#pragma omp parallel
    {
#pragma omp for private(i1, j1, i, j, constant)
        for (i1 = 0; i1 < N; i1 += bs) {
            for (j1 = 0; j1 < N; j1 += bs) {
                for (i = i1; i < MIN(i1 + bs, N); ++i) {
                    for (j = j1; j < MIN(j1 + bs, N); ++j) {
                        f[i][j] = 0;
                        if (gridspacing * i >= 1 && gridspacing * i <= 1 + 1.0 / 3 && gridspacing * j >= 1.0 / 3 &&
                            gridspacing * j <= 2.0 / 3) {
                            f[i][j] = constant;
                        }
                    }
                }
            }
        }
    }
    return f;
}

double **generateU(int N, int bs) {
    double **u = malloc_2d(N + 2, N + 2);
    int i1, j1, i, j;
#pragma omp parallel
    {
#pragma omp for  private(i1, j1, i, j)
        for (i1 = 0; i1 < N + 2; i1 += bs) {
            for (j1 = 0; j1 < N + 2; j1 += bs) {
                for (i = i1; i < MIN(i1 + bs, N + 2); ++i) {
                    for (j = j1; j < MIN(j1 + bs, N + 2); ++j) {
                        u[i][j] = (i == 0 || i == N + 1 || j == N + 1) ? 20.0 : 0.0;
                    }
                }
            }
        }
    }
    return u;
}
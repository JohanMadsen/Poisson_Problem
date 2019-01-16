#include "init.h"
#include "datatools.h"

double **generateF(int N, double gridspacing) {
    double **f = malloc_2d(N, N);
    double constant=gridspacing*gridspacing*200;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            f[i][j] = 0;
            if (gridspacing * i >= 1 && gridspacing * i <= 1 + 1.0 / 3 && gridspacing * j >= 1.0 / 3 &&
                gridspacing * j <= 2.0 / 3) {
                f[i][j] = constant;
            }
        }
    }
    return f;
}

double **generateU(int N) {
    double **u = malloc_2d(N + 2, N + 2);
    for (int i = 0; i < N + 2; ++i) {
        for (int j = 0; j < N + 2; ++j) {
            if (i == 0 || i == N + 1 || j == N + 1) {
                u[i][j] = 20;
            } else {
                u[i][j] = 0;
            }
        }
    }
    return u;
}
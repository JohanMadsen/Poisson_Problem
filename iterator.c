#include <math.h>
#include "iterator.h"
#include <stdio.h>
#include <omp.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

double gaussIteration(double ***u, double ***f, int N) {
    double sum = 0;
    double temp;

    for (int i = 1; i < N + 1; ++i) {
        for (int j = 1; j < N + 1; ++j) {
            temp = (*u)[i][j];
            (*u)[i][j] = 0.25 * ((*u)[i][j - 1] + (*u)[i][j + 1] + (*u)[i - 1][j] + (*u)[i + 1][j] +
                                 (*f)[i - 1][j - 1]);
            sum += ((*u)[i][j] - temp) * ((*u)[i][j] - temp);
        }
    }
    return sqrt(sum);
}


double jacobiIteration(double ***u, double ***uold, double ***f, int N) {
    int i, j;
    double sum = 0.0;
    double temp;

#pragma omp parallel for private(i, j, temp) reduction(+: sum)
    for (i = 1; i < N + 1; ++i) {
        for (j = 1; j < N + 1; ++j) {
            (*u)[i][j] = 0.25 * ((*uold)[i][j - 1] + (*uold)[i][j + 1] + (*uold)[i - 1][j] + (*uold)[i + 1][j] +
                                 (*f)[i - 1][j - 1]);
            temp = (*u)[i][j] - (*uold)[i][j];
            sum += temp * temp;
        }
    }
    return sqrt(sum);
}

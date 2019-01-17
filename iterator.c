#include <math.h>
#include "iterator.h"
#include <stdio.h>

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

double gaussIterationBlk(double ***u, double ***f, int N, int bs) {
    double sum = 0;
    double temp;

    for (int i1 = 1; i1 < N + 1; i1 += bs) {
        for (int j1 = 1; j1 < N + 1; j1 += bs) {
            for (int i = i1; i < MIN(i1 + bs, N + 1); ++i) {
                for (int j = j1; j < MIN(j1 + bs, N + 1); ++j) {
                    temp = (*u)[i][j];
                    (*u)[i][j] = 0.25 * ((*u)[i][j - 1] + (*u)[i][j + 1] + (*u)[i - 1][j] + (*u)[i + 1][j] +
                                         (*f)[i - 1][j - 1]);
                    sum += ((*u)[i][j] - temp) * ((*u)[i][j] - temp);
                }
            }
        }
    }
    return sqrt(sum);
}

double jacobiIterationBlk(double ***u, double ***uold, double ***f, int N, int bs) {
    double sum = 0;
    int i1, j1, i, j;
#pragma omp parallel
    {
#pragma omp for private(i1, j1, i, j) reduction(+: sum) schedule(runtime)
        for (i1 = 1; i1 < N + 1; i1 += bs) {
            for (j1 = 1; j1 < N + 1; j1 += bs) {
                for (i = i1; i < MIN(i1 + bs, N + 1); ++i) {
                    for (j = j1; j < MIN(j1 + bs, N + 1); ++j) {
                        (*u)[i][j] =
                                0.25 * ((*uold)[i][j - 1] + (*uold)[i][j + 1] + (*uold)[i - 1][j] + (*uold)[i + 1][j] +
                                        (*f)[i - 1][j - 1]);
                        sum += ((*u)[i][j] - (*uold)[i][j]) * ((*u)[i][j] - (*uold)[i][j]);
                    }
                }
            }
        }
    }
    return sqrt(sum);
}

double jacobiIteration(double ***u, double ***uold, double ***f, int N, double *d) {
    int i, j;
    double sum = 0;
    #pragma omp for private(i, j) schedule(runtime) reduction(+: sum)
        for (i = 1; i < N + 1; ++i) {
            for (j = 1; j < N + 1; ++j) {
                (*u)[i][j] = 0.25 * ((*uold)[i][j - 1] + (*uold)[i][j + 1] + (*uold)[i - 1][j] + (*uold)[i + 1][j] +
                                     (*f)[i - 1][j - 1]);
                sum += ((*u)[i][j] - (*uold)[i][j]) * ((*u)[i][j] - (*uold)[i][j]);
            }
        }
    #pragma omp single
        {
            (*d) = sqrt(sum);
        }
    return sqrt(sum);
}

double jacobiIteration2(double ***u, double ***uold, double ***f, int N) {

    for (int i = 1; i < N + 1; ++i) {
        for (int j = 1; j < N + 1; ++j) {
            (*u)[i][j] = (*f)[i - 1][j - 1];
        }
    }
    for (int i = 1; i < N + 1; ++i) {
        for (int j = 1; j < N + 1; ++j) {
            if (i < N) {
                (*u)[i + 1][j] += (*uold)[i][j];
            }
            if (i > 1) {
                (*u)[i - 1][j] += (*uold)[i][j];
            }
            if (j < N) {
                (*u)[i][j + 1] += (*uold)[i][j];
            }
            if (j > 1) {
                (*u)[i][j - 1] += (*uold)[i][j];
            }
        }
    }
    double sum = 0;
    for (int i = 1; i < N + 1; ++i) {
        for (int j = 1; j < N + 1; ++j) {
            (*u)[i][j] *= 0.25;
            sum += ((*u)[i][j] - (*uold)[i][j]);
        }
    }
    return sqrt(sum);
}


double jacobiIteration2Blk(double ***u, double ***uold, double ***f, int N, int bs) {
    for (int i1 = 1; i1 < N + 1; i1 += bs) {
        for (int j1 = 1; j1 < N + 1; j1 += bs) {
            for (int i = i1; i < MIN(i1 + bs, N + 1); ++i) {
                for (int j = j1; j < MIN(j1 + bs, N + 1); ++j) {
                    (*u)[i][j] = (*f)[i - 1][j - 1];
                }
            }
        }
    }
    for (int i1 = 1; i1 < N + 1; i1 += bs) {
        for (int j1 = 1; j1 < N + 1; j1 += bs) {
            for (int i = i1; i < MIN(i1 + bs, N + 1); ++i) {
                for (int j = j1; j < MIN(j1 + bs, N + 1); ++j) {
                    if (i < N) {
                        (*u)[i + 1][j] += (*uold)[i][j];
                    }
                    if (i > 1) {
                        (*u)[i - 1][j] += (*uold)[i][j];
                    }
                    if (j < N) {
                        (*u)[i][j + 1] += (*uold)[i][j];
                    }
                    if (j > 1) {
                        (*u)[i][j - 1] += (*uold)[i][j];
                    }
                }
            }
        }
    }
    double sum = 0;
    for (int i1 = 1; i1 < N + 1; i1 += bs) {
        for (int j1 = 1; j1 < N + 1; j1 += bs) {
            for (int i = i1; i < MIN(i1 + bs, N + 1); ++i) {
                for (int j = j1; j < MIN(j1 + bs, N + 1); ++j) {
                    (*u)[i][j] *= 0.25;
                    sum += ((*u)[i][j] - (*uold)[i][j]);
                }
            }
        }
    }
    return sqrt(sum);
}

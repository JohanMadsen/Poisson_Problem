#include "datatools.h"
#include <stdio.h>
#include <stdlib.h>

void swap(double ***m1, double ***m2) {
    double **tmp;
    tmp = *m1;
    *m1 = *m2;
    *m2 = tmp;
}

double ** malloc_2d(int m, int n) {
    int i;

    if (m <= 0 || n <= 0)
        return NULL;

    double **A = malloc(m * sizeof(double *));
    if (A == NULL)
        return NULL;

    A[0] = malloc(m * n * sizeof(double));
    if (A[0] == NULL) {
        free(A);
        return NULL;
    }
    for (i = 1; i < m; i++)
        A[i] = A[0] + i * n;

    return A;
}

void free_2d(double **A) {
    free(A[0]);
    free(A);
}

void print_matrix(double ** M, int n){
    printf("\n");
    for (int i = 0; i <n ; ++i) {
        for (int j = 0; j <n ; ++j) {
            printf("%1.2f ",M[i][j]);
        }
        printf("\n");
    }
}

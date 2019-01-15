#include <stdio.h>
#include <malloc.h>
#include <float.h>
#include <math.h>
/* Routine for allocating two-dimensional array */

void swap(double ***m1, double ***m2){
    double **tmp;
    tmp = *m1;
    *m1 = *m2;
    *m2 = tmp;
}

double **
malloc_2d(int m, int n)
{
    int i;

    if (m <= 0 || n <= 0)
        return NULL;

    double **A = malloc(m * sizeof(double *));
    if (A == NULL)
        return NULL;

    A[0] = malloc(m*n*sizeof(double));
    if (A[0] == NULL) {
        free(A);
        return NULL;
    }
    for (i = 1; i < m; i++)
        A[i] = A[0] + i * n;

    return A;
}

void
free_2d(double **A) {
    free(A[0]);
    free(A);
}

double norm(double **m1, double**m2, int N){
    double sum=0;
    for (int i = 1; i <N-1 ; ++i) {
        for (int j = 1; j <N-1 ; ++j) {
            sum+=(m1[i][j]-m2[i][j])*(m1[i][j]-m2[i][j]);
        }
    }
    return sqrt(sum);
}

void jacobiIteration(double ** u, double ** uold,double ** f, double gridspacingsqr, int N){
    for (int i = 1; i <N-1 ; ++i) {
        for (int j = 1; j <N-1 ; ++j) {
            u[i][j]=0.25*(uold[i][j-1]+uold[i][j+1]+uold[i-1][j]+uold[i+1][j]+f[i][j]*gridspacingsqr);
        }
    }
}

void jacobi(int N, int kmax, double threshold,double ** u, double ** f,double gridspacingsqr){
    double ** uold=malloc_2d(N+2,N+2);
    double d=DBL_MAX;
    int k=0;
    while(d>threshold && k<kmax){
        swap(&u,&uold);
        jacobiIteration(u,uold,f,gridspacingsqr,N);
        d=norm(u,uold,N);
        k+=1;
        printf("%f \n ",d);
    }
    free_2d(uold);
}

void gaussIteration(double ** u,double ** f, double gridspacingsqr, int N){
    for (int i = 1; i <N+1 ; ++i) {
        for (int j = 1; j <N+1 ; ++j) {
            u[i][j]=0.25*(u[i][j-1]+u[i][j+1]+u[i-1][j]+u[i+1][j]+f[i-1][j-1]*gridspacingsqr);
        }
    }
}

void gauss(int N, int kmax, double threshold,double ** u, double ** f){

}

double ** generateF(int N, double gridspacing ){
    double ** f=malloc_2d(N,N);
    for (int i = 0; i <N ; ++i) {
        for (int j = 0; j <N ; ++j) {
            f[i][j]=0;
            if (gridspacing*i>=1 && gridspacing*i<=1+1.0/3 && gridspacing*j>=1.0/3 && gridspacing*j<=2.0/3){
                f[i][j]=200.0;
            }
        }
    }
    return f;
}

int main() {
    int N=32;
    int kmax=10000000;
    double threshold=0.1;
    double gridspacing=(double)2/N;
    double ** f = generateF(N,gridspacing);
    double ** u =malloc_2d(N+2,N+2);
    for (int i = 0; i <N+2 ; ++i) {
        for (int j = 0; j <N+2 ; ++j) {
            u[i][j]=1;
        }
    }
    jacobi(N,kmax,threshold,u,f,gridspacing*gridspacing);
    return 0;
}
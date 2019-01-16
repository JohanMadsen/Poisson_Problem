
double gaussIteration(double ***u, double ***f, double gridspacingsqr, int N);
double jacobiIteration(double ***u, double ***uold, double ***f, double gridspacingsqr, int N);
double jacobiIteration2(double ***u, double ***uold, double ***f, double gridspacingsqr, int N);
double gaussIterationBlk(double ***u, double ***f, double gridspacingsqr, int N, int bs);
double jacobiIterationBlk(double ***u, double ***uold, double ***f, double gridspacingsqr, int N, int bs);

#ifndef C_ITERATOR_H
#define C_ITERATOR_H

#endif //C_ITERATOR_H

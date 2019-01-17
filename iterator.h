#define FLOP 9

double gaussIteration(double ***u, double ***f, int N);

void jacobiIteration(double ***u, double ***uold, double ***f, int N, double * d);

double jacobiIteration2(double ***u, double ***uold, double ***f, int N);

double gaussIterationBlk(double ***u, double ***f, int N, int bs);

double jacobiIterationBlk(double ***u, double ***uold, double ***f, int N, int bs);

double jacobiIteration2Blk(double ***u, double ***uold, double ***f, int N, int bs);

#ifndef C_ITERATOR_H
#define C_ITERATOR_H

#endif //C_ITERATOR_H

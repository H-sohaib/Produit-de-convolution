#include "convolution.h"
#include <stdio.h>

void main()
{
  srand((unsigned int)time(NULL));

  int nk = 3;
  Matrice k = get_random_matrix(nk, 10);
  print2DArray(k, nk);

  printf(" \n");
  int n = 7;
  Matrice m = get_random_matrix(n, 10);
  print2DArray(m, n);

  printf(" \n");
  Matrice out_m = conv_matrices(m, n, k, nk);
  print2DArray(out_m, n);

  freeMatrix(out_m, n);
  freeMatrix(m, n);
  freeMatrix(k, nk);
};
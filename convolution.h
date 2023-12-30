#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int **Matrice;

void freeMatrix(Matrice m, int n)
{
  // Free allocated memory for the original matrix
  for (int i = 0; i < n; i++)
  {
    free(m[i]);
  }
  free(m);
}

void print2DArray(Matrice m, int n)
{
  // Find the maximum number of digits in the matrix
  int maxDigits = 0;
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      int digits = snprintf(NULL, 0, "%d", m[i][j]);
      if (digits > maxDigits)
        maxDigits = digits;
    }
  }

  // Print the matrix with a fixed width for each element
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      printf("%*d\t", maxDigits, m[i][j]);
    }
    printf("\n");
  }
}

void printMatrix(Matrice matrix, int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%d\t", matrix[i][j]);
    }
    printf("\n");
  }
}

Matrice get_random_matrix(int n, int range)
{
  Matrice matrix = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++)
  {
    matrix[i] = (int *)malloc(n * sizeof(int)); // Allocate memory for each row
    for (int j = 0; j < n; j++)
    {
      matrix[i][j] = rand() % range;
    }
  }
  return matrix;
}

int trace_matrice(Matrice m, int n)
{
  int trace = 0;
  for (int i = 0; i < n; i++)
  {
    trace += m[i][i];
  }
  return trace;
}

Matrice flip_matrice(Matrice matrix, int n)
{
  Matrice fliped = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++)
  {
    fliped[i] = (int *)malloc(n * sizeof(int));
    for (int j = 0; j < n; j++)
    {
      fliped[i][j] = matrix[n - i - 1][n - j - 1];
    }
  }
  return fliped;
}

Matrice surroundWithZeros(Matrice m, int n)
{
  n = n + 2; // add 1 to initiale size the add 0s
  // Allocate memory for the new matrix
  Matrice newMatrix = (int **)calloc(n, sizeof(int *));
  for (int i = 0; i < n; i++)
  {
    newMatrix[i] = (int *)calloc(n, sizeof(int));
  }

  // Copy the original content into the interior of the new matrix
  for (int i = 1; i < n - 1; i++)
  {
    for (int j = 1; j < n - 1; j++)
    {
      newMatrix[i][j] = m[i - 1][j - 1];
    }
  }

  return newMatrix;
}

Matrice conv_matrices(Matrice m_input, int n_input, Matrice kernel, int n_kernel)
{
  kernel = flip_matrice(kernel, n_kernel);

  int n_sm = n_input + 2;
  Matrice sm = (int **)calloc(n_sm, sizeof(int *));
  for (int i = 0; i < n_sm; i++)
  {
    sm[i] = (int *)calloc(n_sm, sizeof(int));
  }

  sm = surroundWithZeros(m_input, n_input);

  Matrice result = (int **)calloc(n_input, sizeof(int *));
  for (int i = 0; i < n_input; i++)
  {
    result[i] = (int *)calloc(n_input, sizeof(int));
  }

  // Convolution operation
  for (int lm = 1; lm <= n_input; lm++)
  {
    for (int cm = 1; cm <= n_input; cm++)
    {

      for (int lk = 0; lk < n_kernel; lk++)
      {
        for (int ck = 0; ck < n_kernel; ck++)
        {
          result[lm - 1][cm - 1] += kernel[lk][ck] * sm[lm - 1 + lk][cm - 1 + ck];
        }
      }
    }
  }

  return result;
}
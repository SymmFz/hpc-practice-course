#include <cblas.h>
#include <stdio.h>

#define M 3
#define N 3
#define K 2
int main()
{
  int i = 0;
  double A[M * K] = {1.0, 2.0, 1.0, -3.0, 4.0, -1.0};
  double B[K * N] = {1.0, 2.0, 1.0, -3.0, 4.0, -1.0};
  double C[M * N] = {.5, .5, .5, .5, .5, .5, .5, .5, .5};

  double alpha = 1.0;
  double beta = 2.0;

  // 行主序
  int lda = K;
  int ldb = N;
  int ldc = N;
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);

  for (i = 0; i < 9; i++)
    printf("%lf ", C[i]);
  printf("\n");

  return 0;
}
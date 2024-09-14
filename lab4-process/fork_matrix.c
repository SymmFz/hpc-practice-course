#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <mpi.h>

#define A(i, j) a[(i) * lda + (j)]
#define B(i, j) b[(i) * ldb + (j)]
#define C(i, j) c[(i) * ldc + (j)]

void random_matrix(int m, int n, double *a, int lda)
{
  /* drand48() generate pseudo-random numbers using the linear congruential algorithm and
     48-bit integer arithmetic. return nonnegative double-precision floating-point values
     uniformly distributed over the interval [0.0, 1.0). */
  double drand48();
  int i, j;

  for (j = 0; j < n; j++)
    for (i = 0; i < m; i++)
      // A(i, j) = drand48();
      A(i, j) = 2.0 * drand48() - 1.0;
}


void naive_gemm(int m, int n, int k, double *a, int lda,
              double *b, int ldb,
              double *c, int ldc)
{
  int i, j, p;
  for (i = 0; i < m; i++) /* Loop over the rows of C */
  {
    for (j = 0; j < n; j++) /* Loop over the columns of C */
    {
      for (p = 0; p < k; p++)
      { /* Update C( i,j ) with the inner product of the ith row of A and the jth column of B */
        C(i, j) = C(i, j) + A(i, p) * B(p, j);
      }
    }
  }
}


int main(int argc, char *argv[]) {

    int matrix_size = 2048;
    double *a = (double *)malloc(matrix_size * matrix_size * sizeof(double));
    double *b = (double *)malloc(matrix_size * matrix_size * sizeof(double));
    double *c = (double *)malloc(matrix_size * matrix_size * sizeof(double));
    random_matrix(matrix_size, matrix_size, a, matrix_size);
    random_matrix(matrix_size, matrix_size, b, matrix_size);
    random_matrix(matrix_size, matrix_size, c, matrix_size);

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process here
        // 计算后半部分
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        naive_gemm(matrix_size / 2, matrix_size, matrix_size, a + matrix_size / 2, matrix_size, b, matrix_size, c + matrix_size / 2, matrix_size);
        printf("ok child\n");
    } else {
        // parent process here
        // 计算前半部分
        printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
        naive_gemm(matrix_size / 2, matrix_size, matrix_size, a, matrix_size, b, matrix_size, c, matrix_size);
        printf("ok parent\n");
    }
    return 0;
}
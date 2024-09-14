#include <stdio.h>
#include "defs.h"
#include <omp.h>

/* Routine for computing C = A * B + C */

// for fish shell, run:
// set -x OMP_NUM_THREADS=8

void MY_MMult(int m, int n, int k, double *a, int lda,
              double *b, int ldb,
              double *c, int ldc)
{
  int i, j, p;
  #pragma omp parallel for private(j, p)
  for (i = 0; i < m; i++) /* Loop over the rows of C */
  {
    for (j = 0; j < n; j++) /* Loop over the columns of C */
    {
      for (p = 0; p < k; p++)
      { /* Update C( i,j ) with the inner product of the ith row of A and the jth column of B */
        C(i, j) = C(i, j) + A(i, p) * B(p, j);
        // printf("Thread %d: i=%d, j=%d, p=%d\n", omp_get_thread_num(), i, j, p);
      }
    }
    // printf("Thread %d: i=%d\n", omp_get_thread_num(), i);
  }
}

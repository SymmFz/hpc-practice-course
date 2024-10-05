#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>
#include "defs.h"
#include <immintrin.h>  // ! SIMD

void REF_MMult(int, int, int, double *, int, double *, int, double *, int);
void MY_MMult(int, int, int, double *, int, double *, int, double *, int);
void copy_matrix(int, int, double *, int, double *, int);
void random_matrix(int, int, double *, int);
void zero_matrix(int, int, double *, int);
double compare_matrices(int, int, double *, int, double *, int);
void print_rowmajor_matrix(int m, int n, double *a, int lda);
double dclock();

int main()
{
  int
      p,
      m, n, k,
      lda, ldb, ldc,
      rep;

  double
      dtime,
      dtime_best,
      gflops,
      diff;

  double
      *a,
      *b, *c,
      *cref, // Reference value computed by REF_MMult()
      *cold; // Random Initialization value

  printf("MY_MMult = [\n");

//   for (p = PFIRST; p <= PLAST; p = 2 * p)
  for (p = PFIRST; p <= PLAST; )
  {
    m = (M == -1 ? p : M);
    n = (N == -1 ? p : N);
    k = (K == -1 ? p : K);

    gflops = 2.0 * m * n * k * 1.0e-09;

    // ldx for column major
    // lda = (LDA == -1 ? m : LDA);
    // ldb = (LDB == -1 ? k : LDB);
    // ldc = (LDC == -1 ? m : LDC);

    lda = (LDA == -1 ? k : LDA);
    ldb = (LDB == -1 ? n : LDB);
    ldc = (LDC == -1 ? n : LDC);

    #if defined(NEW)
        
        #if NEW == t1_MultiBlocks_data_resort || NEW == t1_SIMD || NEW == t1_SIMD_with_unroll4
        // ! 如果使用 SIMD
        a = (double *)_mm_malloc(lda * (k + 1) * sizeof(double), 32);
        b = (double *)_mm_malloc(ldb * n * sizeof(double), 32);
        c = (double *)_mm_malloc(ldc * n * sizeof(double), 32);
        cold = (double *)_mm_malloc(ldc * n * sizeof(double), 32);
        cref = (double *)_mm_malloc(ldc * n * sizeof(double), 32);

        #else
        /* Allocate space for the matrices */
        /* Note: I create an extra column in A to make sure that
        prefetching beyond the matrix does not cause a segfault */
        // a = (double *)malloc(lda * (k + 1) * sizeof(double));
        // b = (double *)malloc(ldb * n * sizeof(double));
        // c = (double *)malloc(ldc * n * sizeof(double));
        // cold = (double *)malloc(ldc * n * sizeof(double));
        // cref = (double *)malloc(ldc * n * sizeof(double));
        #endif
    #endif

    /* Generate random matrices A, B, Cold */
    random_matrix(m, k, a, lda);
    random_matrix(k, n, b, ldb);
    random_matrix(m, n, cold, ldc);

    copy_matrix(m, n, cold, ldc, cref, ldc);

    /* Run the reference implementation so the answers can be compared */
    REF_MMult(m, n, k, a, lda, b, ldb, cref, ldc); //!

    /* Time the "optimized" implementation */
    for (rep = 0; rep < NREPEATS; rep++)
    {
      copy_matrix(m, n, cold, ldc, c, ldc);

      /* Time your implementation */
      dtime = dclock();
      MY_MMult(m, n, k, a, lda, b, ldb, c, ldc);
      dtime = dclock() - dtime;

      if (rep == 0)
        dtime_best = dtime;
      else
        dtime_best = (dtime < dtime_best ? dtime : dtime_best);
    }

    diff = compare_matrices(m, n, c, ldc, cref, ldc);

    printf("%d %le %le \n", p, gflops / dtime_best, diff);



    fflush(stdout);

    free(a);
    free(b);
    free(c);
    free(cold);
    free(cref);

    // 根据 p 的值决定如何递增
    if (p < 256) {
        p *= 2;   // 如果 p >= 256, 则 p 乘以 2
    } else if (p < 1024){
        p += PINC;  // 否则 p 加上 PINC
    } else {
        p *= 2;
    }
  }

  printf("];\n");

  exit(0);
}

// #include "defs.h" // cause error
#include <stdio.h>
#include <immintrin.h>
#include <math.h>

#define A(i, j) a[(i) * lda + (j)]
#define B(i, j) b[(i) * ldb + (j)]
#define C(i, j) c[(i) * ldc + (j)]


const int BLOCK_SIZE = 64;

void calculateBlock(int m, int n, int k, double *a, int lda,
              double *b, int ldb,
              double *c, int ldc)
{
    int i, j, p, t;
    __m256d cm[4], a0, b0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j+=4 * 4) {
            for (t = 0; t < 4; t++) {
                cm[t] = _mm256_load_pd(c + i * ldc + j + t * 4);
            }
            for (p = 0; p < k; p++) {
                a0 = _mm256_broadcast_sd(a + i * lda + p);
                cm[0] += _mm256_mul_pd(a0, _mm256_load_pd(b + p * ldb + j));
                cm[1] += _mm256_mul_pd(a0, _mm256_load_pd(b + p * ldb + j + 4));
                cm[2] += _mm256_mul_pd(a0, _mm256_load_pd(b + p * ldb + j + 8));
                cm[3] += _mm256_mul_pd(a0, _mm256_load_pd(b + p * ldb + j + 12));
            }
            for (t = 0; t < 4; t++) {
                _mm256_store_pd(c + i * ldc + j + t * 4, cm[t]);
            }
        }
    }
}

/* Routine for computing C = A * B + C */
void MY_MMult(int m, int n, int k, double *a, int lda,
              double *b, int ldb,
              double *c, int ldc)
{
  int i, j, p;

  for (i = 0; i < m; i += BLOCK_SIZE)
  {
    for (j = 0; j < n; j += BLOCK_SIZE)
    {
        for (p = 0; p < k; p += BLOCK_SIZE)
        {
            int i_block = i + BLOCK_SIZE > m ? m : i + BLOCK_SIZE;
            int j_block = j + BLOCK_SIZE > n ? n : j + BLOCK_SIZE;
            int p_block = p + BLOCK_SIZE > k ? k : p + BLOCK_SIZE;
    
            calculateBlock(i_block - i, j_block - j, p_block - p, a + i * lda + p, lda,
                           b + p * ldb + j, ldb,
                           c + i * ldc + j, ldc);
        }

    }
  }
}

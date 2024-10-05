#include <stdio.h>
#include <immintrin.h>
#include "defs.h"

/* SIMD 256 with unroll 4 */

void MY_MMult(int m, int n, int k, double *a, int lda,
              double *b, int ldb,
              double *c, int ldc)
{
    int i, j, p, t;
    __m256d cm[4], a0, b0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j+=4 * 4) {
            for (t = 0; t < 4; t++) {
                cm[t] = _mm256_load_pd(c + i * n + j + t * 4);
            }
            for (p = 0; p < k; p++) {
                a0 = _mm256_broadcast_sd(a + i * k + p);
                cm[0] += _mm256_mul_pd(a0, _mm256_load_pd(b + p * n + j));
                cm[1] += _mm256_mul_pd(a0, _mm256_load_pd(b + p * n + j + 4));
                cm[2] += _mm256_mul_pd(a0, _mm256_load_pd(b + p * n + j + 8));
                cm[3] += _mm256_mul_pd(a0, _mm256_load_pd(b + p * n + j + 12));
            }
            for (t = 0; t < 4; t++) {
                _mm256_store_pd(c + i * n + j + t * 4, cm[t]);
            }
        }
    }
}

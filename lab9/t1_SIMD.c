#include <stdio.h>
#include <immintrin.h>
#include "defs.h"

/* SIMD 256 without unroll 4 */

void MY_MMult(int m, int n, int k, double *a, int lda,
              double *b, int ldb,
              double *c, int ldc)
{
    int i, j, p;
    __m256d c0, a0, b0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j+=4) {
            c0 = _mm256_load_pd(c + i * n + j);
            for (p = 0; p < k; p++) {
                a0 = _mm256_broadcast_sd(a + i * k + p);
                b0 = _mm256_load_pd(b + p * n + j);
                c0 = _mm256_add_pd(c0, _mm256_mul_pd(a0, b0));
            }
            _mm256_store_pd(c + i * n + j, c0);
        }
    }
}

#include "defs.h"

const int BLOCK_SIZE = 64;

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
    
            for (int i1 = i; i1 < i_block; i1++)
            {
                for (int j1 = j; j1 < j_block; j1++)
                {
                    for (int p1 = p; p1 < p_block; p1++)
                    {
                        C(i1, j1) += A(i1, p1) * B(p1, j1);
                    }
                }
            }
        }

    }
  }
}

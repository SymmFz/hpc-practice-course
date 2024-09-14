#include "defs.h"
#include <pthread.h>
#include <assert.h>

#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#include <math.h>
// #include <time.h>

struct MatrixThreadArgs {
    int m;
    int n;
    int k;
    double *a;
    int lda;
    double *b;
    int ldb;
    double *c;
    int ldc;
    int section_x_begin;
    int section_x_end;
    int section_y_begin;
    int section_y_end;
};


void *MatrixThreadCalculate(void *arg) {
    // int tid = pthread_self();
    // clock_t start, end;
    // double cpu_time_used;
    // start = clock();

    struct MatrixThreadArgs matrixThreadArgs = *((struct MatrixThreadArgs *) arg);
    int k = matrixThreadArgs.k;
    double *a = matrixThreadArgs.a;
    int lda = matrixThreadArgs.lda;
    double *b = matrixThreadArgs.b;
    int ldb = matrixThreadArgs.ldb;
    double *c = matrixThreadArgs.c;
    int ldc = matrixThreadArgs.ldc;
    int section_x_begin = matrixThreadArgs.section_x_begin;
    int section_x_end = matrixThreadArgs.section_x_end;
    int section_y_begin = matrixThreadArgs.section_y_begin;
    int section_y_end = matrixThreadArgs.section_y_end;

    const int block_size = min(64, (max(section_x_end - section_x_begin, section_y_end - section_y_begin)));
    int block_column_num = ceil((section_x_end - section_x_begin) / block_size);
    int block_row_num = ceil((section_y_end - section_y_begin) / block_size);

    for (int block_x = 0; block_x < block_column_num; block_x++) {
        for (int block_y = 0; block_y < block_row_num; block_y++) {
            int block_base_x = section_x_begin + block_x * block_size;
            int block_base_y = section_y_begin + block_y * block_size;
            int block_end_x = min(section_x_end, block_base_x + block_size);
            int block_end_y = min(section_y_end, block_base_y + block_size);

            for (int i = block_base_x; i < block_end_x; i++) {
                for (int j = block_base_y; j < block_end_y; j++) {
                    for (int p = 0; p < k; p++) {
                        C(i, j) = C(i, j) + A(i, p) * B(p, j);
                    }
                }
            }
        }
    }
    
    // end = clock();
    // printf(".::Thread %d\n", tid);
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    // printf("Thread took %f seconds to execute \n", cpu_time_used);
    // printf("Thread %d\n\n", tid);
    return NULL;
}



void MY_MMult(int m, int n, int k, double *a, int lda,
              double *b, int ldb,
              double *c, int ldc) {
    const int x_seperate = 4, y_seperate = 4, thread_num = x_seperate * y_seperate;

    pthread_t threads[thread_num];
    struct MatrixThreadArgs sectionMatrixThreadArgs[thread_num];
    int rc;

    int section_weight = ceil(n / x_seperate);
    int section_height = ceil(m / y_seperate);
    
    int thread_index = 0;
    for (int section_x = 0; section_x < x_seperate; section_x++) {
        for (int section_y = 0; section_y < y_seperate; section_y++) {
            int section_x_begin = section_x * section_weight;
            int section_x_end = min(n, section_x_begin + section_weight);
            int section_y_begin = section_y * section_height;
            int section_y_end = min(m, section_y_begin + section_height);

            sectionMatrixThreadArgs[thread_index] = (struct MatrixThreadArgs){
                .m = m,
                .n = n,
                .k = k,
                .a = a,
                .lda = lda,
                .b = b,
                .ldb = ldb,
                .c = c,
                .ldc = ldc,
                .section_x_begin = section_x_begin,
                .section_x_end = section_x_end,
                .section_y_begin = section_y_begin,
                .section_y_end = section_y_end
            };
            rc = pthread_create(&threads[thread_index], NULL, MatrixThreadCalculate, &sectionMatrixThreadArgs[thread_index]);
            assert(rc == 0);
            thread_index++;
        }
    }
    // for (int i = 0; i < 8; i++) {
    //     rc = pthread_create(&threads[i], NULL, MatrixThreadCalculate, &sectionMatrixThreadArgs[i]);
    //     assert(rc == 0);
    // }
    for (int i = 0; i < thread_num; i++) {
        rc = pthread_join(threads[i], NULL);  
        assert(rc == 0);
    }
}


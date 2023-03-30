#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define M 1000
#define N 1200
#define K 1000

int A[M][K], B[K][N], C[M][N];

int main()
{
    int i, j, k;
    clock_t start_time, end_time;
    double elapsed_time;

    // Initialize matrices
    for (i = 0; i < M; i++) {
        for (j = 0; j < K; j++) {
            A[i][j] = i + j;
        }
    }
    for (i = 0; i < K; i++) {
        for (j = 0; j < N; j++) {
            B[i][j] = i * j;
        }
    }

    // Multiply matrices sequentially
    start_time = clock();
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end_time = clock(); // Record the end time
    elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    
    
    
    printf("Sequential program: Elapsed time in nearest second is: %f seconds\n", elapsed_time);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define M 1000
#define N 1000
#define K 1000

#define NUM_THREADS 4

double A[M][N], B[N][K], C[M][K];
pthread_t threads[NUM_THREADS];
int thread_args[NUM_THREADS];

void *matrix_mult(void *thread_arg) {
    int tid = *((int*) thread_arg);
    int i, j, k;
    double sum;
    int chunk_size = M / NUM_THREADS;
    int start = tid * chunk_size;
    int end = (tid == NUM_THREADS - 1) ? M : start + chunk_size;

    for (i = start; i < end; i++) {
        for (j = 0; j < K; j++) {
            sum = 0.0;
            for (k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    pthread_exit(NULL);
}

int main() {
    int i, j;
    void *status;

    // Initialize matrices A and B
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < K; j++) {
            B[i][j] = i * j;
        }
    }
    time_t start = time(NULL);
    // Create threads and perform matrix multiplication in parallel
    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, matrix_mult, (void*) &thread_args[i]);
    }

    // Wait for all threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &status);
    }
    printf("elapsed time in nearest second is: %.2f\n", (double)(time(NULL)-start));

    return 0;
}
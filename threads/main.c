#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 8
#define SIZE 512

int arr1[SIZE][SIZE];
int arr2[SIZE][SIZE];
int result[SIZE][SIZE];

void randomIntArrGenerator(int lower, int upper, int size, int arr[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = (rand() % (upper - lower + 1)) + lower;
        }
    }
}

void *matrixMultiplicationThread(void *arg) {
    long tid = *(long *)arg;
    int rowsPerThread = SIZE / MAX_THREADS;
    int start_row = tid * rowsPerThread;
    int end_row = (tid + 1) * rowsPerThread;

    clock_t start_time = clock();
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }

    clock_t end_time = clock();
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Thread %d completed in %.10f seconds\n", tid, time_taken);

//    terminating threads
    pthread_exit(NULL);
}

int main() {
    srand(time(0));

//    generating the random int arrays as matrices
    randomIntArrGenerator(0, 100, SIZE, arr1);
    randomIntArrGenerator(0, 100, SIZE, arr2);

//    creating the threads
    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];

//    running the multiplication
    clock_t start_time = clock();
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, matrixMultiplicationThread, &thread_ids[i]);
    }
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_t end_time = clock();

    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("---\n");
    printf("Matrix Multiplication for size: %d * %d\n", SIZE, SIZE);
    printf("Time Taken: %.10f seconds\n", time_taken);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 8
#define SIZE 512
#define TILE_SIZE 512

int arr1[SIZE][SIZE];
int arr2[SIZE][SIZE];
int result[SIZE][SIZE];

int thread_args[MAX_THREADS][2];

void randomIntArrGenerator(int lower, int upper, int size, int arr[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = (rand() % (upper - lower + 1)) + lower;
        }
    }
}

void *matrixMultiplicationThread(void *arg) {
    int *data = (int *)arg;
    int start_row = data[0];
    int end_row = data[1];

    for (int tile_row = start_row; tile_row < end_row; tile_row++) {
        for (int tile_col = 0; tile_col < SIZE / TILE_SIZE; tile_col++) {
            for (int i = tile_row * TILE_SIZE; i < (tile_row + 1) * TILE_SIZE; i++) {
                for (int j = tile_col * TILE_SIZE; j < (tile_col + 1) * TILE_SIZE; j++) {
                    for (int k = 0; k < SIZE; k++) {
                        result[i][j] += arr1[i][k] * arr2[k][j];
                    }
                }
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(0));

    // Generating the random int arrays as matrices
    randomIntArrGenerator(0, 100, SIZE, arr1);
    randomIntArrGenerator(0, 100, SIZE, arr2);

    // Initializing the result matrix to 0
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
        }
    }

    // Creating the threads
    pthread_t threads[MAX_THREADS];
    int rows_per_thread = SIZE / MAX_THREADS;

    // Starting time measurement
    double start_time = clock();

    for (int i = 0; i < MAX_THREADS; i++) {
        thread_args[i][0] = i * rows_per_thread / TILE_SIZE;
        thread_args[i][1] = (i + 1) * rows_per_thread / TILE_SIZE;
        pthread_create(&threads[i], NULL, matrixMultiplicationThread, (void *)thread_args[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Ending time measurement
    double end_time = clock();
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("---\n");
    printf("Matrix Multiplication for size: %d * %d\n", SIZE, SIZE);
    printf("Time Taken: %.10f seconds\n", time_taken);

    return 0;
}

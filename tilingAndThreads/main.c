#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 4
#define SIZE 512
#define TILE_SIZE 512

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
    int num_tiles_per_thread = (SIZE / TILE_SIZE) / MAX_THREADS;
    int start_tile = tid * num_tiles_per_thread;
    int end_tile = (tid + 1) * num_tiles_per_thread;

    clock_t start_time = clock();
//    tiling algo for each row of first matrix and first column of second matrix for multiplication
    for (int tile_row = start_tile; tile_row < end_tile; tile_row++) {
        for (int tile_col = 0; tile_col < SIZE / TILE_SIZE; tile_col++) {
            for (int i = tile_row * TILE_SIZE; i < (tile_row + 1) * TILE_SIZE; i++) {
                for (int j = tile_col * TILE_SIZE; j < (tile_col + 1) * TILE_SIZE; j++) {
                    result[i][j] = 0;
                    for (int k = 0; k < SIZE; k++) {
                        result[i][j] += arr1[i][k] * arr2[k][j];
                    }
                }
            }
        }
    }

    clock_t end_time = clock();
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Thread %d completed in %.10f seconds\n", tid, time_taken);

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

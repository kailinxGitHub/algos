#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

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
    int *data = (int *)arg;
    int thread_id = data[0];
    int num_threads = data[1];

    int rows_per_thread = SIZE / num_threads;
    int start_row = thread_id * rows_per_thread;
    int end_row = (thread_id == num_threads - 1) ? SIZE : (thread_id + 1) * rows_per_thread;

    for (int tile_row = start_row; tile_row < end_row; tile_row++) {
        for (int tile_col = 0; tile_col < SIZE / TILE_SIZE; tile_col++) {
            for (int i = tile_row * TILE_SIZE; i < (tile_row + 1) * TILE_SIZE && i < SIZE; i++) {
                for (int j = tile_col * TILE_SIZE; j < (tile_col + 1) * TILE_SIZE && j < SIZE; j++) {
                    result[i][j] = 0;
                    for (int k = 0; k < SIZE; k++) {
                        result[i][j] += arr1[i][k] * arr2[k][j];
                    }
                }
            }
        }
    }

    pthread_exit(NULL);
}

double matrixMultiplicationWithThreads(int num_threads) {
    pthread_t threads[num_threads];
    int thread_data[num_threads][2];

    clock_t start_time = clock();

    for (int i = 0; i < num_threads; i++) {
        thread_data[i][0] = i;
        thread_data[i][1] = num_threads;
        pthread_create(&threads[i], NULL, matrixMultiplicationThread, (void *)thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();

    return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

void graphScalingWithThreads(int max_threads) {
    FILE *fptr;
    fptr = fopen("threadScaling.csv", "w");
    fprintf(fptr, "Threads,Time Taken\n");

    for (int num_threads = 1; num_threads <= max_threads; num_threads++) {
        // Initialize matrices and result matrix for each run
        randomIntArrGenerator(0, 100, SIZE, arr1);
        randomIntArrGenerator(0, 100, SIZE, arr2);

        // Reset the result matrix
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                result[i][j] = 0;
            }
        }

        double time_taken = matrixMultiplicationWithThreads(num_threads);
        fprintf(fptr, "%d,%.10f\n", num_threads, time_taken);
    }

    fclose(fptr);
}

int main() {
    srand(time(0));

    graphScalingWithThreads(20);

    return 0;
}
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
    int num_threads = *((int *)arg + 1); // extract the number of threads
    int num_tiles_per_thread = (SIZE / TILE_SIZE) / num_threads;
    int start_tile = tid * num_tiles_per_thread;
    int end_tile = (tid + 1) * num_tiles_per_thread;

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

    pthread_exit(NULL);
}

double matrixMultiplicationWithThreads(int num_threads) {
    pthread_t threads[num_threads];
    long thread_ids[num_threads];
    long thread_data[num_threads][2]; // thread id and number of threads

    clock_t start_time = clock();
    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        thread_data[i][0] = i;
        thread_data[i][1] = num_threads;
        pthread_create(&threads[i], NULL, matrixMultiplicationThread, &thread_data[i]);
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
        randomIntArrGenerator(0, 100, SIZE, arr1);
        randomIntArrGenerator(0, 100, SIZE, arr2);
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

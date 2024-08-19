#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 512  // Matrix size
#define TILE_SIZE 64  // Tile size to improve memory access

int arr1[SIZE][SIZE];
int arr2[SIZE][SIZE];
int result[SIZE][SIZE];

// Struct to hold the start and end indices for each thread
typedef struct {
    int start_row;
    int end_row;
} ThreadData;

// Function to generate random integer matrices
void randomIntArrGenerator(int lower, int upper, int size, int arr[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = (rand() % (upper - lower + 1)) + lower;
        }
    }
}

// Thread function to perform matrix multiplication for a portion of the matrix (based on tiles)
void *matrixMultiplicationThread(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int start_row = data->start_row;
    int end_row = data->end_row;

    // Perform matrix multiplication for the assigned rows (process in tiles)
    for (int i = start_row; i < end_row; i += TILE_SIZE) {
        for (int j = 0; j < SIZE; j += TILE_SIZE) {
            for (int ii = i; ii < i + TILE_SIZE && ii < end_row; ii++) {
                for (int jj = j; jj < j + TILE_SIZE && jj < SIZE; jj++) {
                    for (int k = 0; k < SIZE; k++) {
                        result[ii][jj] += arr1[ii][k] * arr2[k][jj];
                    }
                }
            }
        }
    }
    pthread_exit(NULL);
}

// Function to handle matrix multiplication with the given number of threads
double matrixMultiplicationWithThreads(int num_threads) {
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    int rows_per_thread = SIZE / num_threads;

    // Initialize the result matrix to 0
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
        }
    }

    // Start time measurement
    double start_time = clock();

    // Create threads and assign them portions of the matrix
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == num_threads - 1) ? SIZE : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, matrixMultiplicationThread, (void *)&thread_data[i]);
    }

    // Join threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // End time measurement
    double end_time = clock();
    return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(0));

    // Generate the random integer arrays (matrices)
    randomIntArrGenerator(0, 100, SIZE, arr1);
    randomIntArrGenerator(0, 100, SIZE, arr2);

    // Test with different thread counts
    for (int num_threads = 1; num_threads <= 8; num_threads *= 2) {
        double time_taken = matrixMultiplicationWithThreads(num_threads);
        printf("Time taken with %d threads: %.10f seconds\n", num_threads, time_taken);
    }

    return 0;
}

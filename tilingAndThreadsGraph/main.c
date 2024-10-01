#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 1024

int arr1[SIZE][SIZE];
int arr2[SIZE][SIZE];
int result[SIZE][SIZE];

typedef struct {
    int start_row;
    int end_row;
} ThreadData;

void randomIntArrGenerator(int lower, int upper, int size, int arr[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = (rand() % (upper - lower + 1)) + lower;
        }
    }
}

void *matrixMultiplicationThread(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int start_row = data->start_row;
    int end_row = data->end_row;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

double matrixMultiplicationWithThreads(int num_threads) {
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    int rows_per_thread = SIZE / num_threads;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
        }
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == num_threads - 1) ? SIZE : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, matrixMultiplicationThread, (void *)&thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time;
}

int main() {
    srand(time(0));

    randomIntArrGenerator(0, 100, SIZE, arr1);
    randomIntArrGenerator(0, 100, SIZE, arr2);

    FILE *fptr = fopen("threadScaling.csv", "w");

    for (int num_threads = 1; num_threads <= 32; num_threads *= 2) {
        double time_taken = matrixMultiplicationWithThreads(num_threads);
        printf("Time taken with %d threads: %.10f seconds\n", num_threads, time_taken);
        fprintf(fptr, "%d,%.10f\n", num_threads, time_taken);
    }

    fclose(fptr);

    return 0;
}

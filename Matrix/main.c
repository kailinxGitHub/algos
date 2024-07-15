#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "randIntGen.h"

//dimension of a sub-matrix that the entire multiplication process is broken down into
#define TILE_SIZE 12

//tiled
void matrixMultiplicationTiled(int size, int arr1[size][size], int arr2[size][size], int result[size][size]) {
    for (int i = 0; i < size; i += TILE_SIZE) {
        for (int j = 0; j < size; j += TILE_SIZE) {
            for (int k = 0; k < size; k += TILE_SIZE) {
                // Multiply the tiles
                for (int ii = i; ii < i + TILE_SIZE && ii < size; ++ii) {
                    for (int jj = j; jj < j + TILE_SIZE && jj < size; ++jj) {
                        for (int kk = k; kk < k + TILE_SIZE && kk < size; ++kk) {
                            result[ii][jj] += arr1[ii][kk] * arr2[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

//// not tiled
//void matrixMultiplication(int size, int arr1[size][size], int arr2[size][size], int result[size][size]) {
//    for (int i = 0; i < size; i++) {
//        for (int j = 0; j < size; j++) {
//            result[i][j] = 0;
//            for (int k = 0; k < size; k++) {
//                result[i][j] += arr1[i][k] * arr2[k][j];
//            }
//        }
//    }
//}


float matrixMultiplicationTest(int size) {
    int randomIntArr1[size][size];
    int randomIntArr2[size][size];

    randomIntArrGenerator(0,100, size, randomIntArr1);
    randomIntArrGenerator(0,100, size, randomIntArr2);

    int randomIntArrResult[size][size];
    clock_t time_req;
    time_req = clock();

    matrixMultiplicationTiled(size, randomIntArr1, randomIntArr2, randomIntArrResult);

    time_req = clock() - time_req;
    float timeInSec = (float)time_req/CLOCKS_PER_SEC;

    printf("Matrix Multiplication for size: %d * %d \n", size, size);

    printf("Array 1: \n");
    printShortenOperation(size, randomIntArr1);
    printf("---\n");

    printf("Array 2: \n");
    printShortenOperation(size, randomIntArr2);
    printf("---\n");

    printf("Array Result: \n");
    printShortenOperation(size, randomIntArrResult);
    printf("---\n");

    printf("Time Taken: %.10f \n", timeInSec);
    printf("---\n");
    printf("---\n");
    return timeInSec;
}

void matrixMultiPowTwoGraph (int numberOfTimes) {
    double power;
    float time;
    for (int i = 0; i < numberOfTimes; i++) {
        power = pow(2.0, i + 1);
        time = matrixMultiplicationTest((int) power);

        FILE *fptr;

        fptr = fopen("matrixGraphTiled.csv", "a");
        if (fptr == NULL) {
            printf("Error opening file!\n");
            return;
        }

        fprintf(fptr, "%f, %.10f\n", power, time);

        fclose(fptr);
    }
}

int main(void) {
    FILE *fptr;
    fptr = fopen("matrixGraphTiled.csv", "w");
    fprintf(fptr,"Powers, Time Taken\n");
    fclose(fptr);

    srand(time(0));

//    for not tiled 9 is as far as it goes without the exit error 139
//    matrixMultiPowTwoGraph(9);

//    for tiled solution
    matrixMultiPowTwoGraph(12);

    return 0;
}
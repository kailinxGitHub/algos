#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "randIntGen.h"

void generateVector(int size, int array[size]) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 101;
    }
}

void vectorAddition(int size, int arr1[size], int arr2[size], int result[size]) {
    for (int i = 0; i < size; i++) {
        result[i] = arr1[i] + arr2[i];
    }
}

void vectorAdditionTest(int size) {
    int vector1[size];
    int vector2[size];
    srand(time(0));
    generateVector(size, vector1);
    generateVector(size, vector2);
    int final[size];

    clock_t time_req;
    time_req = clock();

    vectorAddition(size, vector1, vector2, final);

    time_req = clock() - time_req;
    float timeInSec = (float)time_req/CLOCKS_PER_SEC;

    printf("Vector Addition for size: %d \n", size);
    printVectorOperation(size, vector1, vector2, final);
    printf("Time Taken: %.10f \n", timeInSec);
    printf("---\n");
}

void dotProduct(int size, int arr1[size], int arr2[size], int result[size]) {
    for (int i = 0; i < size; i++) {
        result[i] = arr1[i] * arr2[i];
    }
}

void dotProductTest(int size) {
    int vector1[size];
    int vector2[size];
    srand(time(0));
    generateVector(size, vector1);
    generateVector(size, vector2);
    int final[size];

    clock_t time_req;
    time_req = clock();

    dotProduct(size, vector1, vector2, final);

    time_req = clock() - time_req;
    float timeInSec = (float)time_req/CLOCKS_PER_SEC;

    printf("Vector Multiplication for size: %d \n", size);
    printVectorOperation(size, vector1, vector2, final);
    printf("Time Taken: %.10f \n", timeInSec);
    printf("---\n");
}

int main(void) {
    vectorAdditionTest(100);

    vectorAdditionTest(1000);

    vectorAdditionTest(10000);

    dotProductTest(100);

    dotProductTest(1000);

    dotProductTest(10000);
//    100
//    int HUNDRED = 100;
//    int vector1[HUNDRED];
//    int vector2[HUNDRED];
//    srand(time(0));
//    generateVector(HUNDRED, vector1);
//    generateVector(HUNDRED, vector2);
//    int final[HUNDRED];
//
//    clock_t time_req;
//    time_req = clock();
//
//    vectorAddition(HUNDRED, vector1, vector2, final);
//
//    time_req = clock() - time_req;
//    float timeInSec = (float)time_req/CLOCKS_PER_SEC;
//
//    printVectorOperation(HUNDRED, vector1, vector2, final);
//    printf("Time Taken: %f \n", timeInSec);

    return 0;
}

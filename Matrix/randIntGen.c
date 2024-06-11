//
// Created by Kailin on 5/27/24.
//
#include "randIntGen.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Random Integer Array Generator
// that generates a list of random numbers inside an array
void randomIntArrGenerator(int min, int max, int size, int randomIntArr[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            randomIntArr[i][j] = min + rand() % (max - min + 1);
        }
    }
}

void printShortenArray(int size, int arr[size]) {
    for (int i = 0; i < 2 && i < size; i++) {
        printf("%d, ", arr[i]);
    }
    printf("..., ");
    for (int i = size - 2; i < size && i >= 2; i++) {
        if (i == size - 1) {
            printf("%d", arr[i]);
        } else {
            printf("%d, ", arr[i]);
        }
    }
    printf("\n");
}

void printArray(int size, int arr[size]) {
    for (int i = 0; i < size; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

void printOperation(int size, int arr[size][size]) {
    for (int i = 0; i < size; i++) {
        printArray(size, arr[i]);
    }
}

void printShortenOperation(int size, int arr[size][size]) {
    for (int i = 0; i < 1 && i < size; i++) {
        printShortenArray(size, arr[i]);
    }
    printf("...\n");
    for (int i = size - 1; i < size && i >= 1; i++) {
        printShortenArray(size, arr[i]);
    }
}
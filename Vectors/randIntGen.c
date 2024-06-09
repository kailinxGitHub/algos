//
// Created by Kailin on 5/27/24.
//
#include "randIntGen.h"
#include <stdio.h>
#include <stdlib.h>

// Random Integer Array Generator
// that generates a list of random numbers inside an array
int* randomIntArrGenerator(int min, int max, int numWanted) {
//    Dynamic Memory Allocation, I don't understand
    int* randomIntArr = (int*)malloc(numWanted * sizeof(int));

    int size = 0;
    while (size < numWanted) {
        int randInt = rand();
        if (randInt < max && randInt > min) {
            randomIntArr[size++] = randInt;
        }
    }
    return randomIntArr;
}

void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < 3; i++) {
        printf("%d, ", arr[i]);
    }
    printf("..., ");
    for (i = size - 3; i < size; i++) {
        if (i == size - 1) {
            printf("%d", arr[i]);
        } else {
            printf("%d, ", arr[i]);
        }
    }
    printf("\n");
}

void printVectorOperation(int size, int arr1[], int arr2[], int arr3[]) {
    printf("Vector 1: ");
    printArray(arr1, size);
    printf("Vector 2: ");
    printArray(arr2, size);
    printf("Result Vector: ");
    printArray(arr3, size);
}
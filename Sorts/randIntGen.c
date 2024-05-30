//
// Created by Kailin on 5/27/24.
//
#include "randIntGen.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "sorts.h"

// Method to print an array in a horizontal way onto console
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
            printf("%d. ", arr[i]);
            break;
        }
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

void printFloatArray(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
            printf("%.6f. ", arr[i]);
            break;
        }
        printf("%.6f. ", arr[i]);
    }
    printf("\n");
}

// method to write a line to a file
void writeToFile(char *text) {
    FILE *fptr;

    fptr = fopen("test.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fptr, "%s\n", text);

    fclose(fptr);
}

// Sorting algorithm tester that
// takes in the type of sorting algorithm wanted
// and runs that algorithm with a time stamp showing how long it took for one iteration
float testSort(int arr[], int size, char type[]) {
    clock_t time_req;

    printf("Before: ");
    printArray(arr, size);

    printf("After: ");
    time_req = clock();
    if (strcmp(type, "selectionSort") == 0) {
        selectionSort(arr, size);
    } else if (strcmp(type, "bubbleSort") == 0) {
        bubbleSort(arr, size);
    } else if (strcmp(type, "insertionSort") == 0) {
        insertionSort(arr, size);
    } else if (strcmp(type, "mergeSort") == 0) {
        mergeSort(arr, 0, size);
    } else if (strcmp(type, "quickSort") == 0) {
        quickSort(arr, 0, size);
    }
    time_req = clock() - time_req;

    printArray(arr, size);

    float timeInSec = (float)time_req/CLOCKS_PER_SEC;

    char text[100];
    sprintf(text, "%s Processor time taken: %f seconds\n", type, timeInSec);

    writeToFile(text);

    printf("%s", text);
    return timeInSec;
}

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
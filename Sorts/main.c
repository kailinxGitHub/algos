/* Sorting an array with 100 random integers using:
 * 1. selection sort: with no pointers
 *
 * Kailin Xing 05-24-2024
 * */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "sorts.h"

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

void testSort(int arr[], int size, char type[]) {
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
    }
    time_req = clock() - time_req;

    printArray(arr, size);
    printf("%s Processor time taken: %f "
           "seconds\n",
           type, (float)time_req / CLOCKS_PER_SEC);
}

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

int main(void) {
//    generate random 100 integers stored in an array
    int numWanted = 100;
    int* aHundredInts = randomIntArrGenerator(1, 1000, numWanted);

//    test
    int* aHundredInts2 = randomIntArrGenerator(1, 1000, numWanted);
    int* aHundredInts3 = randomIntArrGenerator(1, 1000, numWanted);

    testSort(aHundredInts, numWanted, "selectionSort");
    testSort(aHundredInts2, numWanted, "bubbleSort");
    testSort(aHundredInts3, numWanted, "insertionSort");

    free(aHundredInts);
    free(aHundredInts2);
    free(aHundredInts3);
}

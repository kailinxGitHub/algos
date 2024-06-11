/* Sorting an array with 100 random integers using:
 * 1. selection sort: with no pointers
 *
 * Kailin Xing 05-24-2024
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "randIntGen.h"
#include "misc.h"

// Generate Sorting Algorithm Compare method that
// takes in two sorting algorithms the user wishes to use
// and runs both of them and compares how each one of them performs (in seconds)
float* genSortsComp (char sortOne[], char sortTwo[], int minInt, int maxInt, int intWanted) {
    char* validSorts[] = {"selectionSort", "bubbleSort", "insertionSort", "mergeSort", "quickSort"};
    int size = sizeof(validSorts)/sizeof(validSorts[0]);

    if (containsStr(validSorts, size, sortOne) && containsStr(validSorts, size, sortTwo)) {
        int* aHundredIntsOne = randomIntArrGenerator(minInt, maxInt, intWanted);
        int* aHundredIntsTwo = randomIntArrGenerator(minInt, maxInt, intWanted);

        float* pair = (float*)malloc(2 * sizeof(float));
        if (pair != NULL) {
            pair[0] = testSort(aHundredIntsOne, intWanted, sortOne);
            pair[1] = testSort(aHundredIntsTwo, intWanted, sortTwo);
        }

        return pair;
    } else {
        return NULL;
    }
}

int main(void) {
    float* timePair = genSortsComp("bubbleSort", "quickSort", 1, 1000, 1000);
    free(timePair);
}
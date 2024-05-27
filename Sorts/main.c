/* Sorting an array with 100 random integers using:
 * 1. selection sort: with no pointers
 *
 * Kailin Xing 05-24-2024
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "randIntGen.h"

bool containsStr(const char *stringArr[], int size, const char *target) {
    for (int i = 0; i < size; i++) {
        if (strcmp(stringArr[i], target) == 0) {
            return true;
        }
    }
    return false;
}

float *genSortsComp (char sortOne[], char sortTwo[], int minInt, int maxInt, int intWanted) {
    char* validSorts[] = {"selectionSort", "bubbleSort", "insertionSort", "mergeSort", "quickSort"};
    int size = sizeof(validSorts)/sizeof(validSorts[0]);

    if (containsStr(validSorts, size, sortOne) && containsStr(validSorts, size, sortTwo)) {
        int *aHundredIntsOne = randomIntArrGenerator(minInt, maxInt, intWanted);
        int *aHundredIntsTwo = randomIntArrGenerator(minInt, maxInt, intWanted);

        float *times = (float *)malloc(2 * sizeof(float));

        times[0] = testSort(aHundredIntsOne, intWanted, sortOne);
        times[1] = testSort(aHundredIntsTwo, intWanted, sortTwo);

        free(aHundredIntsOne);
        free(aHundredIntsTwo);

        return times;
    } else {
        return NULL;
    }
}

void genSortsCompLoop (char sortOne[], char sortTwo[], int minInt, int maxInt, int intWanted, int timesWanted) {
    float timeArr[2][timesWanted];

    for (int i = 0; i < timesWanted; i++) {
        float *iteration = genSortsComp(sortOne, sortTwo, minInt, maxInt, intWanted);

        if (iteration != NULL) {
            timeArr[0][i] = iteration[0];
            timeArr[1][i] = iteration[1];
        } else {
            timeArr[0][i] = 0;
            timeArr[1][i] = 0;
        }

//        debug
        printArray(timeArr, timesWanted);
    }

    float SortOneArr[timesWanted], SortTwoArr[timesWanted];
    for (int i = 0; i < timesWanted; i++) {
        SortOneArr[i] = timeArr[0][i];
        SortTwoArr[i] = timeArr[1][i];
    }

    float sortOneAvg = 0;
    for(int i = 0; i < timesWanted; i++) {
        sortOneAvg += SortOneArr[i];
    }
    sortOneAvg = sortOneAvg/timesWanted;

    float sortTwoAvg = 0;
    for(int i = 0; i < timesWanted; i++) {
        sortTwoAvg += SortTwoArr[i];
    }
    sortTwoAvg = sortTwoAvg/timesWanted;

    printf("%s Processor time taken: %f "
           "seconds\n"
           "%s Processor time taken: %f "
           "seconds\n",
           sortOne, sortOneAvg/CLOCKS_PER_SEC, sortTwo, sortTwoAvg/CLOCKS_PER_SEC);
}

int main(void) {
    genSortsCompLoop("bubbleSort", "quickSort", 1, 1000, 100, 10000);
}
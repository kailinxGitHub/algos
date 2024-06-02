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

// Generate Sorts Compare Loop is a method that
// generates a time pair (pair of floating point times of two types of sorting algorithm)
// for every iteration and finding the average time for each of the two sorting algorithms
void genSortsCompLoop (char sortOne[], char sortTwo[], int minInt, int maxInt, int intWanted, int timesWanted) {
    float timeArr[timesWanted][2];

    for (int i = 0; i < timesWanted; i++) {

//        txt write
        char text[100];
        sprintf(text, "Iteration number: %d", i);
        writeToFile(text);

        float* timePair = genSortsComp(sortOne, sortTwo, minInt, maxInt, intWanted);

        if (timePair != NULL) {
            timeArr[i][0] = timePair[0];
            timeArr[i][1] = timePair[1];
        } else {
            timeArr[i][0] = 0;
            timeArr[i][1] = 0;
        }

        // debug
        printFloatArray(timePair, 2);

        free(timePair);

//        txt write
        writeToFile("---");
    }

    float sortOneAvg = getPairIthAverage(timeArr, timesWanted, 0);
    float sortTwoAvg = getPairIthAverage(timeArr, timesWanted, 1);

    char iterationMessage[100];
    sprintf(iterationMessage, "For a total of %d iterations \n", timesWanted);

    char averageMessage[200];
    sprintf(averageMessage, "%s Processor Average time taken: %.8f "
                  "seconds\n"
                  "%s Processor Average time taken: %.8f "
                  "seconds\n",
            sortOne, sortOneAvg, sortTwo, sortTwoAvg);

    printf("--- \n");
    printf("%s", iterationMessage);
    printf("%s", averageMessage);

    //        txt write
    writeToFile("---");
    writeToFile(iterationMessage);
    writeToFile(averageMessage);
}

int main(void) {
    genSortsCompLoop("bubbleSort", "quickSort", 1, 1000, 100, 1000);
}
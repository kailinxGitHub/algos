//
// Created by Kailin on 5/30/24.
//
// Method to print an array in a horizontal way onto console
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

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

    fptr = fopen("bubbleSort_VS_quickSort.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fptr, "%s\n", text);

    fclose(fptr);
}

// helper method to check if a string exists within an array of strings
bool containsStr(char* stringArr[], int size, const char *target) {
    for (int i = 0; i < size; i++) {
        if (strcmp(stringArr[i], target) == 0) {
            return true;
        }
    }
    return false;
}

// given an array of float pairs, find the average of all ith float in the pair
float getPairIthAverage(float arr[][2], int size, int ith) {
    float total = 0;

    for (int i = 0; i < size; i++) {
        total += arr[i][ith];
    }

    return total/(float)size;
}
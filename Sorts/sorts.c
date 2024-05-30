//
// Created by Kailin on 5/25/24.
//
#include "sorts.h"
#include <stdio.h>

// Selection Sort Function that
// takes in an unordered list and its size
// orders the list by selecting the smallest from the unordered part of the list and then
// swapping it into the ordered part of the list to ensure a one list operation
void selectionSort(int unordered[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int smallest = i;
        for (int j = i + 1; j < size; j++) {
            if (unordered[j] < unordered[smallest]) {
                smallest = j;
            }
        }
        int temp = unordered[i];
        unordered[i] = unordered[smallest];
        unordered[smallest] = temp;
    }
}

// Bubble Sort Function that
// takes in an unordered list and its size
// compares two numbers and swap if needed
// keep iterating until the whole unordered list is exhausted
// keep looping the iterations until no swapping is needed in a whole loop
void bubbleSort(int unordered[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (unordered[j] > unordered[j+1]) {
                int temp = unordered[j];
                unordered[j] = unordered[j+1];
                unordered[j+1] = temp;
            }
        }
    }
}

// Selection Sort Function that
// takes in an unordered list and its size
// iterates through all the elements in the unsorted
// sort the list by placing the next element into the sorted portion of the array
// loop until all is sorted
void insertionSort(int unordered[], int size) {
    for (int i = 1; i < size; i++) {
        int key = unordered[i];
        int j = i - 1;

        while (j >= 0 && unordered[j] > key) {
            unordered[j + 1] = unordered[j];
            j = j - 1;
        }
        unordered[j + 1] = key;
    }
}

// Merge Sort helper function called merge
// that takes in the array, start, mid, and end
// and merges two sorted subarrays into a single sorted array
void merge (int unordered[], int start, int mid, int end) {
    int a1 = mid - start + 1;
    int a2 = end - mid;

    int leftArr[a1], rightArr[a2];

    for (int i = 0; i < a1; i++) {
        leftArr[i] = unordered[start + i];
    }
    for (int j = 0; j < a2; j++) {
        rightArr[j] = unordered[mid + 1 + j];
    }

    int i = 0, j = 0;

    int mergedArrIndex = start;
    while (i < a1 && j < a2) {
        int leftCurrItem = leftArr[i];
        int rightCurrItem = rightArr[j];

        if (leftCurrItem <= rightCurrItem) {
            unordered[mergedArrIndex] = leftCurrItem;
            i++;
        } else {
            unordered[mergedArrIndex] = rightCurrItem;
            j++;
        }
        mergedArrIndex++;
    }

    while (i < a1) {
        unordered[mergedArrIndex] = leftArr[i];
        i++;
        mergedArrIndex++;
    }
    while (j < a2) {
        unordered[mergedArrIndex] = rightArr[j];
        j++;
        mergedArrIndex++;
    }
}

// Merge Sort main function that recursively divides the array
// into smaller subarrays until each subarray has only one element
// then merges the subarrays back together in sorted order
void mergeSort (int unordered[], int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(unordered, start, mid);
        mergeSort(unordered, mid + 1, end);
        merge(unordered, start, mid, end);
    }
}

// Quick Sort helper method that
// sets the pivot and rearranges the elements
int partition (int unordered[], int start, int end) {
    int pivot = unordered[end];
    int i = start - 1;

    for (int j = start; j <= end - 1; j++) {
        if (unordered[j] < pivot) {
            i++;
            int temp = unordered[i];
            unordered[i] = unordered[j];
            unordered[j] = temp;
        }
    }

    int temp = unordered[i + 1];
    unordered[i + 1] = unordered[end];
    unordered[end] = temp;

    return (i + 1);
}

// Quick Sort function that recursively sorts every element
void quickSort (int unordered[], int start, int end) {
    if (start < end) {
        int pivotIndex = partition(unordered, start, end);

        quickSort(unordered, start, pivotIndex - 1);
        quickSort(unordered, pivotIndex + 1, end);
    }
}
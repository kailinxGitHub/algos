//
// Created by Kailin on 5/25/24.
//
#include "sorts.h"
#include <stdio.h>

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
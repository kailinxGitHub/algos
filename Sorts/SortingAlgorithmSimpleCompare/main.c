#include <stdio.h>

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

int main(void) {
    int testArr[] = { 10, 20, 9, 3, 11, 100, 31 };
    int size = sizeof(testArr)/sizeof(testArr[0]);
    bubbleSort(testArr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", testArr[i]);
    }
    printf("\n");

    return 0;
}

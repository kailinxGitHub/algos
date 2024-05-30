//
// Created by Kailin on 5/30/24.
//

#ifndef MISC_H
#define MISC_H

#include <stdbool.h>

void printArray(int arr[], int size);
void printFloatArray(float arr[], int size);
void writeToFile(char *text);
bool containsStr(char* stringArr[], int size, const char *target);
float getPairIthAverage(float arr[][2], int size, int ith);

#endif //MISC_H

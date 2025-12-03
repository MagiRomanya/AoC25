#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

#define MAX_DIGITS 20

int checkValidIdPart1(long id) {
    char idString[MAX_DIGITS];
    const int nDigits = (int)(ceil(log10(id))+1);
    sprintf(idString, "%li", id);

    int halfNDigits = nDigits/2;

    for (int i = 0; i < halfNDigits; ++i) {
        if (idString[i] != idString[halfNDigits+i]) {
            return 1;
        }
    }
    return 0;
}

int checkValidIdPart2(long id) {
    char idString[MAX_DIGITS] = {0};
    const int nDigits = ceil(log10(id));
    sprintf(idString, "%li", id);
    int halfNDigits = nDigits/2;
    for (int size = 1; size <= halfNDigits; ++size) {
        if (nDigits % size != 0) continue;
        int isSequence = 1;
        char sequence[MAX_DIGITS] = {0};
        memcpy(sequence, idString, size);
        for (int j = 0; j < nDigits - (size - 1); j+=size) {
            char blockJ[MAX_DIGITS] = {0};
            memcpy(blockJ, &(idString[j]), size);
            if (strcmp(sequence, blockJ) != 0) {
                isSequence = 0;
                break;
            }
        }
        if (isSequence) return 0;
    }

    return 1;
}


int main()
{
    // HACK Comma terminated
    char* idRanges = readEntireFile("data/2.dat");

    // TESTING
    // char* idRanges = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124,";
    // char* idRanges = "2121212118-2121212124,";

    int rPtr = 0;
    long totalPart1 = 0; // sum of the value of the invalid ids
    long totalPart2 = 0; 
    while (idRanges[rPtr] != '\0' && idRanges[rPtr] != '\n') {
        char* idRange = &(idRanges[rPtr]);
        int cPtr = 0; // comma ptr
        int dPtr = 0; // dash ptr
        while ((idRange[(cPtr++)] != ',')) {
            if (idRange[(cPtr)] == '-') {
                dPtr = cPtr + 1;
            }
        }

        char digitsLow[MAX_DIGITS] = {0};
        char digitsHigh[MAX_DIGITS] = {0};

        int nDigitsLow = dPtr - 1;
        int nDigitsHigh = cPtr - dPtr - 1;
        if (nDigitsLow > MAX_DIGITS || nDigitsHigh > MAX_DIGITS) {
            printf("MAX_DIGITS too short!\n");
            return 1;
        }
        memcpy(digitsLow, idRange, nDigitsLow);
        memcpy(digitsHigh, &(idRange[dPtr]), nDigitsHigh);

        long numLow = atol(digitsLow);
        long numHigh = atol(digitsHigh);

        long id = numLow;
        for (; id <= numHigh; id++) {
            int valid1 = checkValidIdPart1(id);
            int valid2 = checkValidIdPart2(id);
            if (!valid1) {
                totalPart1 += id;
            }
            if (!valid2) {
                totalPart2 += id;
            }
        }

        rPtr += cPtr;
    }
    printf("(Part 1) Adding up all the invalid IDs produces %li.\n", totalPart1);
    printf("(Part 2) Adding up all the invalid IDs produces %li.\n", totalPart2);
    return 0;
}

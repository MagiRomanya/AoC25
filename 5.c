#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utilities.h"

#define MAX_DIGITS 20

int main() {

    char* data = readEntireFile("data/5.dat");
    // char* data = "3-5\n10-14\n16-20\n12-18\n\n1\n5\n8\n11\n17\n32\n";
    int bPtr = 0;
    int rangeCount = 0;
    // find blank line
    while (!((data[++bPtr] == '\n') && (data[bPtr+1] == '\n'))) {
        if (data[bPtr] == '-') rangeCount++;
    }

    // Parse ranges
    long *ranges = malloc(sizeof(long) * rangeCount * 2);
    int rPtr = 0;
    int rIndex = 0;
    while (data[rPtr] != '\n') { // Iterate ranges
        int nlPtr = 0; // newline
        int dPtr = 0; // dash
        while (data[rPtr + (nlPtr++)] != '\n') {
            if (data[rPtr + nlPtr] == '-') dPtr = nlPtr;
        }
        char lowStr[MAX_DIGITS] = {0};
        char highStr[MAX_DIGITS] = {0};
        memcpy(lowStr, &(data[rPtr]), dPtr);
        memcpy(highStr, &(data[rPtr+dPtr+1]), nlPtr - dPtr - 2);
        long low = atol(lowStr);
        long high = atol(highStr);
        ranges[rIndex] = low;
        ranges[rIndex+1] = high;
        rIndex += 2;
        rPtr+=nlPtr;
    }

    // PART 1
    int freshCountPart1 = 0;
    char* indexData = &(data[bPtr+2]);
    int iPtr = 0;
    while (indexData[iPtr] != '\0') { // Iterate indices
        int nlPtr = 0;
        while (indexData[iPtr + (nlPtr++)] != '\n') {}
        char indexStr[MAX_DIGITS] = {0};
        memcpy(indexStr, &(indexData[iPtr]), nlPtr - 1 /* skip \n */);
        long index = atol(indexStr);

        for (int i = 0; i < 2*rangeCount; i+=2) {
            long low = ranges[i];
            long high = ranges[i+1];
            if ((index >= low) && (index <= high)) { // Check if in range (fresh)
                freshCountPart1++;
                break; // If it is fresh we don't need to keep looking
            }
        }

        iPtr+=nlPtr;
    }

    // PART 2
    long freshCountPart2 = 0;

    char* alreadyAccounted = malloc(sizeof(char) * rangeCount + 1);
    memset(alreadyAccounted, 'n', sizeof(char) * rangeCount);
    alreadyAccounted[rangeCount] = '\0';

    for (int i = 0; i < 2*rangeCount; i+=2) {
        const long lowA = ranges[i];
        const long highA = ranges[i+1];
        long low = lowA;
        long high = highA;
        if (alreadyAccounted[i/2] == 'y') continue; // This range is already been counted
        int increasedRange = 1;
        while (increasedRange) {
            increasedRange = 0;
            for (int j = i + 2; j < 2*rangeCount; j+=2) {
                if (alreadyAccounted[j/2] == 'y') continue; // This range is already been counted
                const long lowB = ranges[j];
                const long highB = ranges[j+1];

                // Ranges Overlap
                if ((low <= highB) && (high >= lowB)) {
                    alreadyAccounted[j/2] = 'y'; // The jth range is merged with the ith range
                    if (highB > high) {
                        high = highB;
                        increasedRange = 1;
                    }
                    if (lowB < low) {
                        low = lowB;
                        increasedRange = 1;
                    }
                }
            }
        }
        printf("low = %li, high = %li, count = %li\n", low, high, high - low + 1);
        freshCountPart2 += high - low + 1 /* inclusive intervals */;
    }
    printf("%s\n", alreadyAccounted);

    printf("(Part 1) Count of fresh ingredients %i\n", freshCountPart1);
    printf("(Part 2) Count of fresh ingredients %li\n", freshCountPart2);
    return 0;
}

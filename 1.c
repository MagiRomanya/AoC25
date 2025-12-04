#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

#define MAX_DIGITS 4


int main() {
    char* instructions = readEntireFile("data/1.dat");
    // TESTING
    /* char* instructions = "L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82\n"; */
    int iPtr = 0;

    // The dial starts by pointing at 50.
    int state = 50;
    int zeroCounterPart1 = 0;
    int zeroCounterPart2 = 0;
    while (instructions[iPtr] != '\0') {
        int nlPtr = 0;
        while (instructions[iPtr + (nlPtr++)] != '\n') {}
        char digits[MAX_DIGITS] = {0};
        int nDigits = nlPtr - 2;
        memcpy(digits, &(instructions[iPtr+1]), nDigits);
        int num = atoi(digits);

        int state0 = state;
        switch (instructions[iPtr]) {
            case 'L': {
                state -= num;
                break;
            }
            case 'R': {
                state += num;
                break;
            }
            printf("UNREACHABLE\n");
            return 1;
        }

        if (state <= 0 || state >= 100) {
            if (state > 0) { // positive
                zeroCounterPart2 += state / 100;
            }
            else if (state == 0) {
                zeroCounterPart2++;
            }
            else { // negative
                // Count how many -100s we passed
                int zeros = abs(state) / 100; 
        
                // If we started at >0, then we crossed an extra time
                if (state0 > 0) zeros++;

                zeroCounterPart2 += zeros;
            }
        }

        state = state % 100;
        if (state < 0) {
            state = 100 + state;
        }

        if (state == 0) {
            zeroCounterPart1++;
        }
        iPtr += nlPtr;
    }
    printf("(Part1) Password = %i\n", zeroCounterPart1);
    printf("(Part2) Password = %i\n", zeroCounterPart2);
}

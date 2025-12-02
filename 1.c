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
    int zeroCounter = 0;
    while (instructions[iPtr] != '\0') {
        int nlPtr = 0;
        while (instructions[iPtr + (nlPtr++)] != '\n') {}
        char digits[MAX_DIGITS] = {0};
        int nDigits = nlPtr - 2;
        memcpy(digits, &(instructions[iPtr+1]), nDigits);
        int num = atoi(digits);

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
        }

        state = state % 100;
        if (state < 0) {
            state = 100 + state;
        }
        if (state == 0) {
            zeroCounter++;
        }
        iPtr += nlPtr;
    }
    printf("Password = %i\n", zeroCounter);
}

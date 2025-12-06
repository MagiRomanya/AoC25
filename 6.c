#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

#define MAX_DIGITS 10

int isDigit(char c) {
    return ((c == '0') || (c == '1') ||(c == '2') ||(c == '3') ||(c == '4') ||(c == '5') ||(c == '6') ||(c == '7') ||(c == '8') ||(c == '9'));
}

int isOperation(char c) {
    return ((c == '+') || (c == '*'));
}

int main() {
    // char* problem = readEntireFile("data/6.dat");
    char* problem = " 123 328 51 64\n 45 64  387 23\n 6 98  215 314\n*   +   *   +  \n";
    // Get problem sizes
    int ptr = 0;
    int lines = 0;
    int spaces = 0;
    while (problem[ptr++] != '\0') {
        if (problem[ptr] == '\n') { lines++; }
        if ((lines == 0) && (problem[ptr] == ' ')) {
            if (problem[ptr-1] != ' ') {
                spaces++;
            }
        }
    }
    const int rows = lines - 1; // The last line is for operations
    const int cols = spaces + 1; // there is 1 value more than separators
    printf("rows = %i, cols = %i\n", rows, cols);
    int *inputs = malloc(sizeof(int) * rows * cols);
    // Parse the problem
    ptr = 0;
    int valuePtr = 0;
    int operationPtr = 0;
    char* operations = malloc((cols + 1) * sizeof(char)); // remove space paddings
    operations[cols] = '\0';
    while (problem[ptr] != '\0') {
        int dPtr = 0; // digit pointer
        while (isDigit(problem[ptr + (dPtr++)])) {}

        if (dPtr > 1) { // We are dealing with a number
            char digits[MAX_DIGITS] = {0};
            memcpy(digits, &(problem[ptr]), dPtr - 1);
            inputs[valuePtr++] = atoi(digits);
        }
        if (isOperation(problem[ptr])) {
            operations[operationPtr++] = problem[ptr];
        }
        ptr += dPtr;
    }

    // Do the math homework:
    long totalPart1 = 0;
    for (int i = 0; i < cols; ++i) {
        char operation = operations[i];
        long localResult = 0;
        if (operation == '*') localResult = 1;
        for (int j = 0; j < rows; ++j) {
            int number = inputs[cols*j + i];
            printf("number = %i\n", number);
            switch (operation) {
                case '*': {
                    localResult *= number;
                    break;
                }
                case '+': {
                    localResult += number;
                    break;
                }
                // UNREACHABLE
                return 1;
            }
        }
        totalPart1 += localResult;
    }
    printf("(Part1) Homework result = %li\n", totalPart1);
    return 0;
}

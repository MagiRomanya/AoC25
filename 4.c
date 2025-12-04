#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

static inline int getIndex(int cols, int row, int col) {
    return (cols + 1 /*accounting the \n*/) * row + col;  // index
}

int countRollsAndRemoveThem(int rows, int cols, char* diagram, char* newDiagram) {
    int nRolls = 0;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int i = getIndex(cols, row, col);
            if ('@' == diagram[i]) { // paper cell
                int count = 0;
                if (col - 1 >= 0) { 
                    if ('@' == diagram[getIndex(cols, row, col - 1)]) count++; // left
                    if ((row - 1 >= 0) && ('@' == diagram[getIndex(cols, row - 1, col - 1)])) count++; // up left
                    if ((row + 1 < rows) && ('@' == diagram[getIndex(cols, row + 1, col - 1)])) count++; // down left
                }
                if (col + 1 < cols) {
                    if ('@' == diagram[getIndex(cols, row, col + 1)]) count++;  // right
                    if ((row - 1 >= 0) && ('@' == diagram[getIndex(cols, row - 1, col + 1)])) count++; // up right
                    if ((row + 1 < rows) && ('@' == diagram[getIndex(cols, row + 1, col + 1)])) count++; // down right
                }

                if (row - 1 >= 0) { 
                    if ('@' == diagram[getIndex(cols, row - 1, col)]) count++; // up
                }
                if (row + 1 < rows) {
                    if ('@' == diagram[getIndex(cols, row + 1, col)]) count++;  // down
                }
                // The forklifts can only access a roll of paper if there are fewer than four rolls of paper in the eight adjacent positions.
                if (count < 4) {
                    newDiagram[i] = 'x';
                    nRolls++;
                }
                // printf("row = %i, col = %i, count = %i\n", row, col, count);
            }
            else if ('x' == diagram[i]) newDiagram[i] = '.';
        }
    }
    return nRolls;
}

int main() {
    #if 1 
    char* diagram = readEntireFile("data/4.dat");
    size_t length = strlen(diagram);
    #else
    char* diagramSource = "..@@.@@@@.\n@@@.@.@.@@\n@@@@@.@.@@\n@.@@@@..@.\n@@.@@@@.@@\n.@@@@@@@.@\n.@.@.@.@@@\n@.@@@.@@@@\n.@@@@@@@@.\n@.@.@@@.@.\n";
    size_t length = strlen(diagramSource);
    char* diagram = malloc(length+1);
    strcpy(diagram, diagramSource);
    #endif

    // Check diagram dimensions
    int cols = 0, rows = 0;
    while (diagram[++cols] != '\n') {}
    while (diagram[(cols + 1 /*accounting the \n*/) * (++rows)] != '\0') {}

    char* newDiagram = malloc(length+1);
    strcpy(newDiagram, diagram);

    printf("rows = %i, cols = %i\n", rows, cols);
    int removedRollsPart1 = countRollsAndRemoveThem(rows, cols, diagram, newDiagram);

    int removedRollsPart2 = removedRollsPart1;
    strcpy(diagram, newDiagram);
    printf("%s\n", diagram);
    for (;;) {
        int removedRolls = countRollsAndRemoveThem(rows, cols, diagram, newDiagram);
        printf("removedRolls = %i\n", removedRolls);
        if (removedRolls == 0) break;
        strcpy(diagram, newDiagram);
        printf("%s\n", diagram);
        removedRollsPart2 += removedRolls;
    }

    printf("(Part 1) Removed Rolls = %i\n", removedRollsPart1);
    printf("(Part 2) Removed Rolls = %i\n", removedRollsPart2);

    return 0;
}

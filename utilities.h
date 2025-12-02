#ifndef AOC_UTILITIES_H
#define AOC_UTILITIES_H

#include <stdio.h>
#include <stdlib.h>

char* readEntireFile(char* path) {
    FILE *file = fopen(path, "r");
    // Get file size
    fseek(file, 0, SEEK_END);
    int fsize = ftell(file);
    rewind(file);
    // Get file content to memory
    char *fileContents = malloc(fsize + 1);
    fread(fileContents, fsize, sizeof(char), file);
    fclose(file);
    return fileContents;
}


#endif // AOC_UTILITIES_H

#include <stdlib.h>
#include <stdio.h>

#include "utilities.h"

int computeMaxJoltageBruteForce(char *rating, int n) {
    char pair[3] = {0};
    int max = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            pair[0] = rating[i];
            pair[1] = rating[j];
            int num = atoi(pair);
            if (num > max) max = num;
            // printf("%s\n", pair);
        }
    }
    return max;
}

#define MAX_DIGITS 12

long long computeMaxJoltage(char *rating, int n, int n_digits) {
    char joltNumber[MAX_DIGITS] = {0};
    int start = 0;
    for (int a = 0; a < n_digits; ++a) {
        int imax = start;
        for (int i = start; i < n - (n_digits - 1 - a); ++i) {
            if (rating[imax] < rating[i]) imax = i;
        }
        start = imax + 1;
        joltNumber[a] = rating[imax];
    }
    long long num = atoll(joltNumber);
    // printf("num = %lli\n", num);
    return num;
}


int main() {
    // char *ratings = "987654321111111\n811111111111119\n234234234234278\n818181911112111\n";
    char *ratings = readEntireFile("data/3.dat");
    int rPtr = 0;
    long long totalJoltage2 = 0;
    long long totalJoltage12 = 0;
    while (ratings[rPtr] != '\0') {
        char *rating = &(ratings[rPtr]);
        int nlPtr = 0;
        while (rating[nlPtr++] != '\n') {}

        long long joltage2 = computeMaxJoltage(rating, nlPtr - 1, 2);
        long long joltage12 = computeMaxJoltage(rating, nlPtr - 1, 12);
        totalJoltage2 += joltage2;
        totalJoltage12 += joltage12;

        rPtr += nlPtr;
    }
    printf("(Part 1) Total Joltage (2) = %lli\n", totalJoltage2);
    printf("(Part 2) Total Joltage (12) = %lli\n", totalJoltage12);
    return 0;
}

##
# AoC 2025
#
# @file
# @version 0.1

all: day1 day2 day3

day1: 1.c
	cc 1.c -o 1.out

day2: 2.c
	cc 2.c -lm -o 2.out

day3: 3.c
	cc 3.c -o 3.out

# end

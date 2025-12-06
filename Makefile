##
# AoC 2025
#
# @file
# @version 0.1

all: day1 day2 day3 day4 day5 day6

day1: 1.c
	cc 1.c -o 1.out

day2: 2.c
	cc 2.c -lm -o 2.out

day3: 3.c
	cc 3.c -o 3.out

day4: 4.c
	cc 4.c -o 4.out

day5: 5.c
	cc 5.c -o 5.out

day6: 6.c
	cc 6.c -o 6.out

# end

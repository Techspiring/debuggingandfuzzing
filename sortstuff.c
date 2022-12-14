// Copyright 2022 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "./sortstuff.h"

uint8_t SortArray(int32_t* arr, size_t n) {
	//Get number of elements in array ...
	uint8_t changed = 1;
	int16_t tmp;
	
	// Simple, yet inefficient way of sorting, Bubble sort.
	while(changed > 0) {
		changed = 0;

		for(size_t pos = 1; pos < n; pos++) {
			if(arr[pos] < arr[pos-1]) {
				tmp = arr[pos];
				arr[pos] = arr[pos-1];
				arr[pos-1] = tmp;
				changed = 1;
			}
		}
	}
	return 0;
}

uint8_t BinarySearch(int32_t number, int32_t* arr, size_t n) {
	size_t middle, step;
	if(!isSorted(arr, n)) return 2;
	// Intentional error: should be hibit(n-1);
	middle = hibit(n);
	step = middle;
	// Search value by successive approximation
	while(arr[middle] != number) {
		// Mo more steps to take, abort mission.
		if(step == 0) return 0;
		//printf("@%d\t%d\t%d\t%d\t%d\n", middle, n, arr[middle], number, step);
		// Remove last step, if it was too much
		if(arr[middle] > number) middle ^= step;
		step = step >> 1;
		
		// Take next step, same position if step would cause an overflow.
		if((middle|step) < n) middle |= step;
	}
	return 1;
}
bool isSorted(int32_t* arr, size_t n) {
	return (checkSorting(arr, n) & ORDER_ASC) > 0;
}

uint8_t checkSorting(int32_t* arr, size_t n) {
	// Ascending, Descending, (strict) monotonic
	uint8_t res = ORDER_ASC|ORDER_DESC|ORDER_STRICT;
	for(size_t i = 1; i < n; i++) {
		if(arr[i] < arr[i-1]) res &= ~ORDER_ASC;
		else if(arr[i] > arr[i-1]) res &= ~ORDER_DESC;
		else if(arr[i] == arr[i-1]) res &= ~ORDER_STRICT;
		
		if(!(res & (ORDER_ASC|ORDER_DESC))) return 0;
	}
	return res;
}

size_t hibit(size_t n) {
    n |= (n >> 1);
    n |= (n >> 2);
    n |= (n >> 4);
    n |= (n >> 8);
    n |= (n >> 16);
    n |= (n >> 32);
    return n - (n >> 1);
}

int32_t* GenerateRandomArray(size_t size, uint32_t seed) {
	int32_t* arr;
	
	// Set the randomizer seed
	srand(seed);
	
	// Generate array
	arr = (int32_t*) malloc(size * sizeof(int32_t));
	
	// Generate randomized numbers with randomized signs.
	for(size_t i = 0; i < size; i++) {
		if(rand() % 2) arr[i] = rand();
		else arr[i] = -rand();
	}
	return arr;
}


uint8_t LinearSearch(int32_t number, int32_t* arr, size_t n) {
	// Iterate over all elements, return 1 on match.
	for(size_t i = 0; i < n; i++) {
		if(arr[i] == number) return 1;
		else if(arr[i] > number) return 0;
	}
	return 0;
}
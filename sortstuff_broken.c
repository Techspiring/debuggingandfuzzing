// Copyright 2022 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#include <stdint.h>
#include <stdio.h>
#include "./sortstuff.h"

uint8_t SortArray(int32_t* arr, size_t n) {
	//Get number of elements in array ...
	uint8_t changed = 1;
	int16_t tmp;
	
	// Simple, yet inefficient way of sorting.
	while(changed > 0) {
		changed = 0;
		for(size_t pos = 1; pos <= n; pos++) {
			if(arr[pos] < arr[pos-1]) {
				tmp = arr[pos];
				arr[pos] = arr[pos-1];
				arr[pos-1] = tmp;
				changed = 1;
			}
		}
	}
	return 1;
}

uint8_t BinarySearch(int32_t number, int32_t* arr, size_t n) {
	size_t middle, step;
	if(!isSorted(arr, n)) return 2;
	middle = hibit(n);
	step = middle;
	// Search value by successive approximation
	while(arr[middle] != number) {
		// Mo more steps to take, abort mission.
		if(step == 0) return 0;
		// Remove last step, if it was too much
		if(arr[middle] > number) middle ^= step;
		step = step >> 1;
		
		// Take next step, same position if step would cause an overflow.
		if((middle|step) < n) middle |= step;
	}
	return 1;
}
bool isSorted(int32_t* arr, size_t n) {
	return (checkSorting(arr, n)) > 0;
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
// Copyright 2022 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "./sortstuff.h"

#define megarand() (size_t)((rand()<<45)^(rand()<<30)^(rand()<<15)^(rand()))

int32_t arr0[5] = {5,4,3,2,1};
int32_t arr1[5] = {0,10,20,30,40};
int32_t arr2[0] = {}; 
int32_t arr3[5] = {0,0,0,0,0}; 
int32_t arr4[2] = {1, -1};
int32_t arr5[4] = {0,10,20,30};
int main(void) {
	time_t rawtime;
	struct tm * timeinfo;
	printf("Testing base cases.\n");

	// Test if sorting check works fine
	assert(0 == isSorted(arr0, sizeof(arr0)/sizeof(arr0[0])));
	assert(1 == isSorted(arr1, sizeof(arr1)/sizeof(arr1[0])));
	assert(1 == isSorted(arr2, sizeof(arr2)/sizeof(arr2[0])));
	assert(1 == isSorted(arr3, sizeof(arr3)/sizeof(arr3[0])));
	assert(0 == isSorted(arr4, sizeof(arr4)/sizeof(arr4[0])));
	assert(1 == isSorted(arr5, sizeof(arr5)/sizeof(arr5[0])));
	
	// Sort stuff
	SortArray(arr0, sizeof(arr0)/sizeof(arr0[0]));
	SortArray(arr1, sizeof(arr1)/sizeof(arr1[0]));
	SortArray(arr2, sizeof(arr2)/sizeof(arr2[0]));
	SortArray(arr3, sizeof(arr3)/sizeof(arr3[0]));
	SortArray(arr4, sizeof(arr4)/sizeof(arr4[0]));
	
	// Should be ordered ascending. If not, Sort stuff most likely failed.
	assert(1 == isSorted(arr0, sizeof(arr0)/sizeof(arr0[0])));
	assert(1 == isSorted(arr1, sizeof(arr1)/sizeof(arr1[0])));
	assert(1 == isSorted(arr2, sizeof(arr2)/sizeof(arr2[0])));
	assert(1 == isSorted(arr3, sizeof(arr3)/sizeof(arr3[0])));
	assert(1 == isSorted(arr4, sizeof(arr4)/sizeof(arr4[0])));

	assert(1 == BinarySearch(5, arr0, sizeof(arr0)/sizeof(arr0[0])));
	assert(1 == BinarySearch(0, arr1, sizeof(arr1)/sizeof(arr1[0])));
	assert(0 == BinarySearch(5, arr2, sizeof(arr2)/sizeof(arr2[0])));
	assert(1 == BinarySearch(0, arr3, sizeof(arr3)/sizeof(arr3[0])));
	assert(1 == BinarySearch(0, arr4, sizeof(arr4)/sizeof(arr4[0])));
	assert(1 == BinarySearch(20, arr5, sizeof(arr5)/sizeof(arr5[0])));

	size_t rand_tests = 0;
	size_t test_arr_size;
	size_t seed = 0;
	int32_t seek = 0;
	int32_t* arr;
	
	//for(rand_tests = 25; rand_tests > 0; rand_tests--) {
	while(1) {
		rand_tests++;
		test_arr_size = megarand() % 11119;
		
		seed = megarand();
		printf("%d: Testing with %zu random numbers seed %zu.\n", rand_tests, test_arr_size, seed);
		arr = GenerateRandomArray(test_arr_size, seed);
		
		SortArray(arr, test_arr_size);
		assert(1 == isSorted(arr, test_arr_size));
		
		for(uint8_t rand_find = 0; rand_find < 50; rand_find++) {
			seek = megarand()%test_arr_size;
			assert(1 == BinarySearch(arr[seek], arr, test_arr_size));
			assert(1 == LinearSearch(arr[seek], arr, test_arr_size));
		}
		free(arr);
	}
	
	
	
	return 0;
}
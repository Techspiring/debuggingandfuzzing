// Copyright 2022 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#ifndef sortstuff_h
#define sortstuff_h
#include <stdint.h>
#include <stdbool.h>

#define ORDER_ASC		0x08
#define ORDER_DESC		0x04
#define ORDER_STRICT	0x02

/* SortArray
 * Sorts the given array arr of length n ascending.
 * Always returns 0.
 */
uint8_t SortArray(int32_t* arr, size_t n);

/* BinarySearch
 * Applies binary search (successive approximation) to find the given number in arr.
 *
 * Returns:
 * 0 = number is not contained in array
 * 1 = number is contained in array
 * 2 = array is unsorted, no binary search possible
 */
uint8_t BinarySearch(int32_t number, int32_t* arr, size_t n);

/* CheckSorting
 * Checks if an array is sorted.
 *
 * Returns:
 * 0x00 = not sorted
 * 0x04 = Ordered descending
 * 0x06 = Ordered strictly descending
 * 0x08 = Ordered ascending
 * 0x0A = Ordered strictly ascending
 */
uint8_t checkSorting(int32_t* arr, size_t n);

/* isSorted
 * Checks if an array is sorted ascending.
 *
 * Returns:
 * 0 = not sorted ascending
 * 1 = sorted ascending
 */
bool isSorted(int32_t* arr, size_t n);

/* hibit
 * Returns a bitmask of the highest bit set in the given integer n.
 */
size_t hibit(size_t n);

/* Generate
 *
 */
int32_t* GenerateRandomArray(size_t size, uint32_t seed);

/* 
 *
 */
uint8_t LinearSearch(int32_t number, int32_t* arr, size_t n);
#endif
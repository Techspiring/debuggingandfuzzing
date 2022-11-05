// Copyright 2022 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#ifndef sortstuff_h
#define sortstuff_h
#include <stdint.h>
#include <stdbool.h>

#define ORDER_ASC		0x08
#define ORDER_DESC		0x04
#define ORDER_STRICT	0x02

uint8_t SortArray(int32_t* arr, size_t n);
uint8_t BinarySearch(int32_t number, int32_t* arr, size_t n);
uint8_t checkSorting(int32_t* arr, size_t n);
bool isSorted(int32_t* arr, size_t n);
size_t hibit(size_t n);
#endif
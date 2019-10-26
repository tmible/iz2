#include "search.h"

size_t max_delta_s(int *arr, size_t n) {
	size_t max_i = 0;
	for (size_t i = 0; i < n - 1; i++) {
		if (arr[i+1] - arr[i] > arr[max_i+1] - arr[max_i]) {
			max_i = i;
		}
	}
	return max_i;
}

int search_s(int *arr, size_t memory_size) {
	size_t n = memory_size / sizeof(int);
	return max_delta_s(arr, n);
}

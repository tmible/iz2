#ifndef SEARCH
#define SEARCH

#include <stdio.h>

enum search_errors {
    MALLOC_IN_SEARCH_RETURNED_NULL = -1,
};

int search_s(int* arr, size_t memory_size);
int search_p(int* arr, size_t memory_size);

#endif

#ifndef SEARCH
#define SEARCH

#include <stdio.h>

enum search_errors {
    MALLOC_IN_SEARCH_RETURNED_NULL = -1,
};

int search(size_t memory_size, int* arr);

#endif

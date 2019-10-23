#ifndef PARALLEL
#define PARALLEL

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

struct thread_info {
	unsigned int *max_i, left, right;
	int *max_d, *arr;
};
int parallel(const char*, int);
void *max_delta(void*);

#endif

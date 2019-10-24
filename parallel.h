#ifndef PARALLEL
#define PARALLEL

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

struct thread_info {
	unsigned int *max_i;
	int 		 *max_d;
	int 		 *arr;
	unsigned int  left;
	unsigned int  right;
};
int search_max_delta_parallel(unsigned int memory_size, const char* file_name, int threads_number, int seed);
void *max_delta(void*);
int compare_d(struct thread_info*, int);

#endif

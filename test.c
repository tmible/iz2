#include <stdio.h>
#include <time.h>
#include <math.h>
#include "sequential.h"
#include "parallel.h"

int test(unsigned int memory_size) {
	clock_t sequential_start_time, sequential_end_time;
	sequential_start_time = clock();
	search_max_delta_sequentially(memory_size, "", time(NULL));
	sequential_end_time = clock();
	printf("время работы последовательного алгоритма: %f s\n", (float)(sequential_end_time - sequential_start_time) / CLOCKS_PER_SEC);

	struct timespec parallel_start_time, parallel_end_time, parallel_time;
	clock_gettime(CLOCK_MONOTONIC, &parallel_start_time);
	search_max_delta_parallel(memory_size, "", 16, time(NULL));
	clock_gettime(CLOCK_MONOTONIC, &parallel_end_time);
	parallel_time.tv_sec = parallel_end_time.tv_sec - parallel_start_time.tv_sec;
	parallel_time.tv_nsec = parallel_end_time.tv_nsec - parallel_start_time.tv_nsec;
	if (parallel_time.tv_nsec < 0) {
  		parallel_time.tv_sec--;
  		parallel_time.tv_nsec += 1000000000L;
	}
    printf("время работы параллельного алгоритма: %ld,%ld s\n", parallel_time.tv_sec, parallel_time.tv_nsec);

	return 0;
}

int main() {
	unsigned int memory_size = 100 * pow(2, 20);
	test(memory_size);
	return 0;
}

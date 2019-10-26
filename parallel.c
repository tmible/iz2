#include "search.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct range_of_slice {
	size_t left;
	size_t right;
};

struct thread_info {
	size_t *max_i;
	int *arr;
	struct range_of_slice range;
};

void init_struct(struct thread_info *ti, size_t *max_i, int *arr, int i, size_t n, int threads_number) {
	ti->max_i = max_i;
	ti->arr = arr;
	ti->range.left = i * (n / threads_number);
	ti->range.right = (n / threads_number) * (i + 1) + 1;
	if (ti->range.right > n) {
		ti->range.right = n;
	}
	return;
}

size_t max_delta_p(int* arr, size_t left, size_t right) {
	size_t max_i = left;
	for (size_t i = left; i < right - 1; i++) {
		if (arr[i+1] - arr[i] > arr[max_i+1] - arr[max_i]) {
			max_i = i;
		}
	}
	return max_i;
}

void *thread_func(void *p) {
	if (p == NULL) {
		pthread_exit(0);
	}
	struct thread_info ti = *((struct thread_info *)p);
	size_t max_i = max_delta_p(ti.arr, ti.range.left, ti.range.right);
	if (((max_i < *(ti.max_i)) && (ti.arr[max_i+1] - ti.arr[max_i] == ti.arr[*(ti.max_i)+1] - ti.arr[*(ti.max_i)])) ||
		(ti.arr[max_i+1] - ti.arr[max_i] > ti.arr[*(ti.max_i)+1] - ti.arr[*(ti.max_i)])) {
		*(ti.max_i) = max_i;
	}
	return 0;
}

int search_p(int* arr, size_t memory_size) {
	size_t n = memory_size / sizeof(int);
	int threads_number = sysconf(_SC_NPROCESSORS_CONF);
    pthread_t thread[threads_number];
    struct thread_info *ti = (struct thread_info *)malloc(threads_number * sizeof(struct thread_info));
	if (ti == NULL) {
		return -1;
	}
    size_t max_i = 0;

    for (int i = 0; i < threads_number; i++) {
		init_struct(&(ti[i]), &max_i, arr, i, n, threads_number);
    	int status = pthread_create(&thread[i], NULL, thread_func, &ti[i]);
    	if (status != 0) {
			pthread_cancel(thread[i]);
		}
	}

    for (int i = 0; i < threads_number; i++) {
    	int status = pthread_join(thread[i], NULL);
    	if (status != 0) {
        	pthread_cancel(thread[i]);
    	}
    }

    free(ti);
    return max_i;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "parallel.h"

struct thread_info {
	unsigned int *max_i, left, right;
	int i, *max_d, *arr;
};

void *max_delta(void *p) {
	struct thread_info ti = *((struct thread_info *)p);
	//printf("поток номер %d запущен, [%d, %d)\n", ti.i , ti.left, ti.right);
	for (int i = ti.left; i < ti.right; i++)
		if (ti.arr[i+1] - ti.arr[i] > *ti.max_d) {
			*ti.max_i = i;
			*ti.max_d = ti.arr[i+1] - ti.arr[i];
		}
	return 0;
}

int parallel(char *file_name, int threads_number) {
	FILE *f = fopen(file_name, "r");
	int *arr = (int*)malloc(100 * pow(2, 20));
	int n = 100 * pow(2, 20) / sizeof(int);
	for (unsigned int i = 0; i < n; i++)
		fscanf(f, "%d", &arr[i]);
	fclose(f);

    pthread_t thread[threads_number];
    struct thread_info *ti = (struct thread_info *)malloc(threads_number * sizeof(struct thread_info));
    unsigned int max_i = 0;
    int max_d = 0;

    for (int i = 0; i < threads_number; i++) {
		ti[i].i = i;
    	ti[i].max_i = &max_i;
    	ti[i].max_d = &max_d;
		ti[i].arr = arr;
    	ti[i].left = i * (n / threads_number);
    	ti[i].right = (n / threads_number) * (i + 1) + 1;
    	if (ti[i].right > n) ti[i].right = n;
    	int status = pthread_create(&thread[i], NULL, max_delta, &ti[i]);
    	if (status != 0) {
			printf("main error: can't create thread, status = %d\n", status);
			free(ti);
			free(arr);
			exit(11);
		}
	}

    for (int i = 0; i < threads_number; i++) {
    	int status = pthread_join(thread[i], NULL);
    	if (status != 0) {
        	printf("main error: can't join thread, status = %d\n", status);
        	free(ti);
        	free(arr);
        	exit(12);
    	}
    }

    free(ti);
    free(arr);
    return max_i;
}

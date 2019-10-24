#include "parallel.h"

int compare_d(struct thread_info *ti, int i) {
	return ((*ti).arr[i+1] - (*ti).arr[i]) - *(*ti).max_d;
}

void *max_delta(void *p) {
	if (p != NULL) {
		struct thread_info ti = *((struct thread_info *)p);
		for (int i = ti.left; i < ti.right - 1; i++)
			if ((i < *ti.max_i && compare_d(&ti, i) == 0) || compare_d(&ti, i) > 0) {
				*ti.max_i = i;
				*ti.max_d = ti.arr[i+1] - ti.arr[i];
			}
	}
	return 0;
}

int search_max_delta_parallel(unsigned int memory_size, const char *file_name, int threads_number, int seed) {
	if (threads_number <= 0) return -2;
	int *arr = init_array(memory_size, file_name, seed);
	if (arr == NULL) return -1;
	unsigned int n = memory_size / sizeof(int);

    pthread_t thread[threads_number];
    struct thread_info *ti = (struct thread_info *)malloc(threads_number * sizeof(struct thread_info));
    unsigned int max_i = -1;
    int max_d = 0;

    for (int i = 0; i < threads_number; i++) {
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
			pthread_exit(&ti[i]);
		}
	}

    for (int i = 0; i < threads_number; i++) {
    	int status = pthread_join(thread[i], NULL);
    	if (status != 0) {
        	printf("main error: can't join thread, status = %d\n", status);
        	free(ti);
        	free(arr);
        	pthread_exit(&ti[i]);
    	}
    }

    free(ti);
    free(arr);
    return max_i;
}

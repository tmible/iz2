#include "parallel.h"

void *max_delta(void *p) {
	struct thread_info ti = *((struct thread_info *)p);
	for (int i = ti.left; i < ti.right; i++)
		if (i > 0 && i + 1 < ti.n) {
			if (ti.arr[i+1] - ti.arr[i] > *ti.max_d || (ti.arr[i+1] - ti.arr[i] == *ti.max_d && i < *ti.max_i)) {
				*ti.max_i = i;
				*ti.max_d = ti.arr[i+1] - ti.arr[i];
			}
		}
	return 0;
}

int parallel(const char *file_name, int threads_number) {
	int *arr = (int*)malloc(100 * pow(2, 20));
	int n = 100 * pow(2, 20) / sizeof(int);
	if (file_name[0] != '\0') {
		FILE *f = fopen(file_name, "r");
		for (unsigned int i = 0; i < n; i++)
			fscanf(f, "%d", &arr[i]);
		fclose(f);
	} else {
		srand(time(NULL));
		for (unsigned int i = 0; i < n; i++)
			arr[i] = -30 + rand() % 30;
	}

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
		ti[i].n = n;
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

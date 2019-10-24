#include "sequential.h"

int search_max_delta_sequentially(unsigned int memory_size, const char *file_name, int seed) {
	int *arr = init_array(memory_size, file_name, seed);
	/*(int*)malloc(memory_size);*/
	if (arr == NULL) return -1;
	unsigned int n = memory_size / sizeof(int);
	/*if (file_name[0] != '\0') {
		FILE *f = fopen(file_name, "r");
		if (f == NULL) {
			free(arr);
			return -2;
		}
		for (unsigned int i = 0; i < n; i++)
			fscanf(f, " %d", &arr[i]);
		fclose(f);
	} else {
		srand(seed);
		for (unsigned int i = 0; i < n; i++)
			arr[i] = -30 + rand() % 30;
	}*/
	unsigned int max_i = 0;
	int max_d = 0;
	for (unsigned int i = 0; i < n - 1; i++)
		if (arr[i+1] - arr[i] > max_d) {
			max_i = i;
			max_d = arr[i+1] - arr[i];
		}
	free(arr);
	return max_i;
}

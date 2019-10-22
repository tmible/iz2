#include "sequential.h"

int sequentially(const char *file_name) {
	int *arr = (int*)malloc(100 * pow(2, 20));
	unsigned int n = 100 * pow(2, 20) / sizeof(int);
	if (file_name[0] != '\0') {
		FILE *f = fopen(file_name, "r");
		for (unsigned int i = 0; i < n; i++)
			fscanf(f, " %d", &arr[i]);
		fclose(f);
	} else {
		srand(time(NULL));
		for (unsigned int i = 0; i < n; i++)
			arr[i] = -30 + rand() % 30;
	}
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

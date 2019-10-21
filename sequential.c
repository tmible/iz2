#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sequential.h"

int sequentially(char *file_name) {
	FILE *f = fopen(file_name, "r");
	int *arr = (int*)malloc(100 * pow(2, 20));
	unsigned int n = 100 * pow(2, 20) / sizeof(int);
	for (unsigned int i = 0; i < n; i++)
		fscanf(f, " %d", &arr[i]);
	fclose(f);
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

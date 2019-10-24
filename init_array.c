#include "init_array.h"

int* init_array(unsigned int size, const char *file_name, int seed) {
    int *arr = (int*)malloc(size);
    if (arr == NULL) return NULL;
    unsigned int n = size / sizeof(int);
    if (file_name[0] != '\0') {
		FILE *f = fopen(file_name, "r");
		if (f == NULL) {
			free(arr);
			return NULL;
		}
		for (unsigned int i = 0; i < n; i++)
			fscanf(f, " %d", &arr[i]);
		fclose(f);
	} else {
		srand(seed);
		for (unsigned int i = 0; i < n; i++)
			arr[i] = -30 + rand() % 30;
	}
    return arr;
}

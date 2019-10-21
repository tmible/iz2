#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "sequential.h"
#include "parallel.h"

int main() {
	srand(time(NULL));
	FILE *f = fopen("data", "w");
	unsigned int n = 100 * pow(2, 20) / sizeof(int);
	for (unsigned int i = 0; i < n; i++)
		fprintf(f, "%d ", -30 + rand() % 30);
	fclose(f);
	clock_t start, end;
	start = clock();
	sequentially("data");
	end = clock();
	printf("время работы последовательного алгоритма: %f s\n", (float)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	parallel("data", 16);
    end = clock();
    printf("время работы параллельного алгоритма: %f s\n", (float)(end - start) / CLOCKS_PER_SEC);
    return 0;
}

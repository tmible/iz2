#include <stdio.h>
#include <time.h>
#include "sequential.h"
#include "parallel.h"

int main() {
	clock_t start, end;
	start = clock();
	sequentially("");
	end = clock();
	printf("время работы последовательного алгоритма: %f s\n", (float)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	parallel("", 16);
    end = clock();
    printf("время работы параллельного алгоритма: %f s\n", (float)(end - start) / CLOCKS_PER_SEC);
    return 0;
}

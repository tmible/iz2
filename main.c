/*Сравните и выведите в консоль время работы последовательного и
  параллельного с использованием нескольких потоков алгоритмов,
  каждый из которых выделяет в динамической памяти числовой массив
  размером 100 Мб, заполненный положительными или отрицательными
  значениями температуры за день, после чего выполняет поиск времени,
  когда произошел самый резкий положительный скачок температуры.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "search.h"

#define min_tempereture  -30;
#define max_tempereture  30;

static char *error_messages[] = {
    "Malloc returned NULL",
    "Search failed because malloc returned NULL",
};

enum test_errors {
    MALLOC_RETURNED_NULL = -1,
    SEARCH_FAILED = -2,
};

int random_temperature() {
	int a = min_tempereture;
	a += rand() % max_tempereture
    return a;
}

int* init_array(size_t memory_size, int seed) {
    int *arr = (int*)malloc(memory_size);
    if (arr == NULL) {
        return NULL;
    }
    size_t n = memory_size / sizeof(int);
	srand(seed);
	for (size_t i = 0; i < n; i++) {
		arr[i] = random_temperature();
    }
    return arr;
}

int test(size_t memory_size, char mode) {
	int *arr = init_array(memory_size, time(NULL));
	if (arr == NULL) {
		return -1;
	}

	if (mode == 's') {
		clock_t sequential_start_time = clock();
		search_s(arr, memory_size);
		clock_t sequential_end_time = clock();
		printf("время работы последовательного алгоритма: %.9f s\n", (float)(sequential_end_time - sequential_start_time) / CLOCKS_PER_SEC);
	}

	if (mode == 'p') {
		struct timespec parallel_start_time;
		clock_gettime(CLOCK_MONOTONIC, &parallel_start_time);
		int r = search_p(arr, memory_size);
		if (r < 0) {
			free(arr);
			return r - 1;
		}
		struct timespec parallel_end_time;
		clock_gettime(CLOCK_MONOTONIC, &parallel_end_time);
		struct timespec parallel_time;
		parallel_time.tv_sec = parallel_end_time.tv_sec - parallel_start_time.tv_sec;
		parallel_time.tv_nsec = parallel_end_time.tv_nsec - parallel_start_time.tv_nsec;
		if (parallel_time.tv_nsec < 0) {
	  		parallel_time.tv_sec--;
	  		parallel_time.tv_nsec += 1000000000L;
		}
	    printf("время работы параллельного алгоритма: %ld.%ld s\n", parallel_time.tv_sec, parallel_time.tv_nsec);
	}

	free(arr);
	return 0;
}

int char_to_int(char* c) {
	int r = 0;
	for (int i = 0; c[i] != '\0'; i++) {
		r = r * 10 + (c[i] - '0');
	}
	return r;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "не хватает опции, указывающей на способ поиска\nиспользуйте -s для последовательного алгоритма и -p для параллельного\n");
		return 0;
	}
	if (!(argv[1][0] == '-' && (argv[1][1] == 's' || argv[1][1] == 'p'))) {
		fprintf(stderr, "указана неверная опция\nиспользуйте -s для последовательного алгоритма и -p для параллельного\n");
		return 0;
	}
	size_t memory_size = 100 * pow(2, 20);
	if (argc > 2) {
		memory_size = char_to_int(argv[2]);
	}
	if (argc > 3) {
		if (argv[3][0] == 'K') {
			memory_size *= pow(2, 10);
		}
		if (argv[3][0] == 'M') {
			memory_size *= pow(2, 20);
		}
		if (argv[3][0] == 'G') {
			memory_size *= pow(2, 30);
		}
	}
	int r = test(memory_size, argv[1][1]);
	if (r != 0) {
		fprintf(stderr, "тестирование провалено\n%s\n", error_messages[abs(r)-1]);
	}
	return 0;
}

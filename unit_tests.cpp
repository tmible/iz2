extern "C" {
    #include "search.h"
};
#include <time.h>
#include <math.h>
#include <gtest/gtest.h>

#define min_tempereture  -30;
#define max_tempereture  30;

int random_temperature() {
	int a = min_tempereture;
	a += rand() % max_tempereture
    return a;
}

void init_array(int* arr, size_t memory_size, int seed) {
    size_t n = memory_size / sizeof(int);
    srand(seed);
    for (size_t i = 0; i < n; i++) {
		arr[i] = random_temperature();
    }
    return;
}

TEST(equality_test, t1) {
    size_t memory_size = 100 * pow(2, 20);
    int *arr = (int*)malloc(memory_size);
    if (arr == NULL) FAIL();
    init_array(arr, memory_size, time(NULL));
    ASSERT_EQ(search_s(arr, memory_size), search_p(arr, memory_size));
    init_array(arr, memory_size, time(NULL));
    ASSERT_EQ(search_s(arr, memory_size), search_p(arr, memory_size));
    init_array(arr, memory_size, time(NULL));
    ASSERT_EQ(search_s(arr, memory_size), search_p(arr, memory_size));
    init_array(arr, memory_size, time(NULL));
    ASSERT_EQ(search_s(arr, memory_size), search_p(arr, memory_size));
    free(arr);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

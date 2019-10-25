extern "C" {
    #include "search.h"
};
#include <time.h>
#include <math.h>
#include <gtest/gtest.h>

void init_array(int *arr, size_t memory_size, const char *file_name) {
	FILE *f = fopen(file_name, "r");
    size_t n = memory_size / sizeof(int);
	for (size_t i = 0; i < n; i++) {
		if (fscanf(f, " %d", &arr[i]) == EOF) {
            break;
        }
    }
	fclose(f);
    return;
}

TEST(sequentially_test, standart_test) {
    size_t memory_size = 100 * pow(2, 20);
    int *arr = (int*)malloc(memory_size);
    init_array(arr, memory_size, "test_data_1");
    ASSERT_EQ(2335, search(memory_size, arr));
    init_array(arr, memory_size, "test_data_2");
    ASSERT_EQ(847, search(memory_size, arr));
    init_array(arr, memory_size, "test_data_3");
    ASSERT_EQ(57, search(memory_size, arr));
    init_array(arr, memory_size, "test_data_4");
    ASSERT_EQ(1647, search(memory_size, arr));
    free(arr);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

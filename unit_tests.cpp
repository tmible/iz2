extern "C" {
    #include "sequential.h"
    #include "parallel.h"
};
#include <time.h>
#include <math.h>
#include <gtest/gtest.h>

TEST(sequentially_test, standart_test) {
    unsigned int memory_size = 100 * pow(2, 20);
    ASSERT_EQ(2335, search_max_delta_sequentially(memory_size, "test_data_1", time(NULL)));
    ASSERT_EQ(847, search_max_delta_sequentially(memory_size, "test_data_2", time(NULL)));
    ASSERT_EQ(57, search_max_delta_sequentially(memory_size, "test_data_3", time(NULL)));
    ASSERT_EQ(1647, search_max_delta_sequentially(memory_size, "test_data_4", time(NULL)));
}

TEST(sequentially_test, error_test) {
    unsigned int memory_size = 100 * pow(2, 20);
    ASSERT_EQ(-1, search_max_delta_sequentially(memory_size, "test_data", time(NULL)));
}

TEST(parallel_test, standart_test) {
    unsigned int memory_size = 100 * pow(2, 20);
    ASSERT_EQ(2335, search_max_delta_parallel(memory_size, "test_data_1", 8, time(NULL)));
    ASSERT_EQ(847, search_max_delta_parallel(memory_size, "test_data_2", 8, time(NULL)));
    ASSERT_EQ(57, search_max_delta_parallel(memory_size, "test_data_3", 8, time(NULL)));
    ASSERT_EQ(1647, search_max_delta_parallel(memory_size, "test_data_4", 8, time(NULL)));
}

TEST(parallel_test, error_test) {
    unsigned int memory_size = 100 * pow(2, 20);
    ASSERT_EQ(-1, search_max_delta_parallel(memory_size, "test_data", 8, time(NULL)));
    ASSERT_EQ(-2, search_max_delta_parallel(memory_size, "test_data_1", 0, time(NULL)));
    ASSERT_EQ(-2, search_max_delta_parallel(memory_size, "test_data_2", -13, time(NULL)));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

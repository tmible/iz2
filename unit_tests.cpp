extern "C" {
    #include "sequential.h"
    #include "parallel.h"
};
#include <gtest/gtest.h>

TEST(sequentially_test, t1) {
    ASSERT_EQ(2335, sequentially("test_data_1"));
    ASSERT_EQ(847, sequentially("test_data_2"));
    ASSERT_EQ(57, sequentially("test_data_3"));
    ASSERT_EQ(1647, sequentially("test_data_4"));
}

TEST(parallel_test, t1) {
    ASSERT_EQ(2335, parallel("test_data_1", 1024));
    ASSERT_EQ(847, parallel("test_data_2", 1024));
    ASSERT_EQ(57, parallel("test_data_3", 1024));
    ASSERT_EQ(1647, parallel("test_data_4", 1024));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

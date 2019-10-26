extern "C" {
    #include "main.c"
};
#include <time.h>
#include <math.h>
#include <gtest/gtest.h>

TEST(main_test, error_test) {
    int test_argc = 1;
    char* test_argv[test_argc];
    test_argv[0] = "./iz2";
    ASSERT_EQ(-3, main(test_argc, test_argv));
    test_argc++;
    test_argv = char*[test_argc];
    test_argv[0] = "./iz2";
    test_argv[1] = "-f";
    ASSERT_EQ(-3, main(test_argc, test_argv));
    test_argv[1] = "p";
    ASSERT_EQ(-3, main(test_argc, test_argv));
}

TEST(main_test, memory_size_test) {
    int test_argc = 4;
    char *test_argv[test_argc];
    test_argv[0] = "./iz2";
    test_argv[1] = "-p";
    test_argv[2] = "1";
    test_argv[3] = "Kb";
    ASSERT_EQ(0, main(test_argc, test_argv));
    test_argv[3] = "Mb";
    ASSERT_EQ(0, main(test_argc, test_argv));
    test_argv[3] = "Gb";
    ASSERT_EQ(0, main(test_argc, test_argv));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

cmake_minimum_required(VERSION 2.6)
project(iz2)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(LIB_SOURCE_FILES_S sequential.c)
set(LIB_SOURCE_FILES_P parallel.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic -fPIC -fprofile-arcs -ftest-coverage -D_POSIX_C_SOURCE=199309L")
set(LDFLAGS "${LDFLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_CPPCHECK "cppcheck")

add_library(sequential STATIC ${LIB_SOURCE_FILES_S})
target_link_libraries(sequential -pthread)
target_link_libraries(sequential gcov)
add_library(parallel SHARED ${LIB_SOURCE_FILES_P})
target_link_libraries(parallel -pthread)
target_link_libraries(parallel gcov)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(iz2_s main.c)
target_link_libraries(iz2_s sequential)

add_executable(iz2_p mian.c)
target_link_libraries(iz2_p parallel)

add_executable(run_tests_sequential unit_tests_sequential.cpp)
target_link_libraries(run_tests_sequential ${GTEST_LIBRARIES} sequential)

add_executable(run_tests_parallel unit_tests_parallel.cpp)
target_link_libraries(run_tests_parallel ${GTEST_LIBRARIES} parallel)

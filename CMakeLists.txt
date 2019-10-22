cmake_minimum_required(VERSION 2.6)
project(iz2)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(LIB_SOURCE_FILES_S sequential.c)
set(LIB_SOURCE_FILES_P parallel.c)

add_library(sequential STATIC ${LIB_SOURCE_FILES_S})
add_library(parallel SHARED ${LIB_SOURCE_FILES_P})
target_link_libraries(parallel -pthread)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(iz2 test.c)
target_link_libraries(iz2 sequential parallel)

add_executable(run_tests unit_tests.cpp)
target_link_libraries(run_tests ${GTEST_LIBRARIES} sequential parallel)

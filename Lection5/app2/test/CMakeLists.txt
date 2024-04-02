cmake_minimum_required(VERSION 3.21)
project(test)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(test_ex main.cpp)

target_link_libraries(test_ex gtest)
target_link_libraries(test_ex gtest_main)
target_link_libraries(test_ex products_lib)

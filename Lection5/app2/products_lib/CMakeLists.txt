cmake_minimum_required(VERSION 3.21)
project(products_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(products_lib productAmount.cpp)

target_include_directories(products_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


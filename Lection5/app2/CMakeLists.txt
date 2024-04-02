cmake_minimum_required(VERSION 3.21)
project(app2)

set(CMAKE_CXX_STANDARD 17)

##### Product Lib #####
add_subdirectory(products_lib)
add_subdirectory(test)

add_executable(app2 main.cpp)

target_link_libraries(app2 products_lib)

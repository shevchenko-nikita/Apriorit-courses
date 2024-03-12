cmake_minimum_required(VERSION 3.21)
project(raii_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(raii_project main.cpp guard.cpp)
if(WIN32)
    target_link_libraries(raii_project ws2_32)
endif()
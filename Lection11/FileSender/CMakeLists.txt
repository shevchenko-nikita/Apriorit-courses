cmake_minimum_required(VERSION 3.21)
project(FileSender)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.76 REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    add_executable(server server.cpp fileHandle.cpp)
    add_executable(client client.cpp fileHandle.cpp)

    target_link_libraries(server ${Boost_LIBRARIES} ws2_32)
    target_link_libraries(client ${Boost_LIBRARIES} ws2_32)
endif()


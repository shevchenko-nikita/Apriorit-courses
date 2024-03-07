cmake_minimum_required(VERSION 3.21)
project(Factory_Method)

set(CMAKE_CXX_STANDARD 17)

add_executable(Factory_Method main.cpp "file.h" "report.h" "file.cpp" "txt_report.cpp" "report_creator.h" "csv_report.cpp")

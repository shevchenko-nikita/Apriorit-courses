#include <iostream>

#include "MyVector.h"

int main() {
    MyVector<int> vec;

    vec.push_back(10, "ten");
    vec.push_back(5, "five");
    vec.push_back(12, "twelve");
    vec.push_back(100, "one hundred");

    auto it_begin = vec.begin();

    std::cout << *it_begin.first << ' ' << *it_begin.second;
//    vec.reserve(100);
//    std::cout << vec.m_names->capacity();

//    for(const auto& str : {"five", "ten", "twelve", "kek"}) {
////        try {
////            std::cout << vec[str] << std::endl;
////        }
////        catch (const std::exception& ex) {
////            std::cout << ex.what() << '\n';
////            exit(1);
////        }
////        try {
////            std::pair<const int&, const std::string&> element = vec[1];
////            std::cout << element.first << ' ' << element.second << std::endl;
////        }
////        catch(const std::exception& ex) {
////            std::cout << ex.what() << std::endl;
////            exit(1);
////        }
//    }

}
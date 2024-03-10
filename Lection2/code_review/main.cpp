#include <iostream>

#include "MyVector.h"

int main() {
    MyVector<int> vec;

    vec.push_back(10, "ten");
    vec.push_back(5, "five");
    vec.push_back(12, "twelve");
    vec.push_back(100, "one hundred");

    for(const auto& str : {"five", "ten", "twelve", "kek"}) {
        try {
            std::cout << vec[str] << std::endl;
        }
        catch (const std::exception& ex) {
            std::cout << ex.what() << '\n';
            exit(1);
        }
    }

}
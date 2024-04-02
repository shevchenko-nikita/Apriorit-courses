#include <iostream>

#include "SimpleThreadPool.h"

int main() {
    SimpleThreadPool pool(2);

    auto ft1 = pool.Post([] {
        return 10;
    });

    auto ft2 = pool.Post([] {
        return 20;
    });

    std::cout << "Result 1: " << ft1.get() << std::endl;
    std::cout << "Result 2: " << ft2.get() << std::endl;

}
#include <iostream>

#include "guard.h"
#include "socket_deleter.h"
#include "SharedPtr.h"

#include <memory>

int main() {


    std::shared_ptr<int> x;

    std::shared_ptr<int> y(x);

    x.reset(new int(10));

    std::cout << x.use_count();

}

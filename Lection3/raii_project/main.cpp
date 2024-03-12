#include <iostream>

#include "guard.h"
#include "socket_deleter.h"
#include "SharedPtr.h"

void printSharedPtrInfo(const SharedPtr<int>& ptr) {
    std::cout << ptr.UseCount() << '\n';
    std::cout << ptr.Get() << '\n';
    std::cout << *ptr << '\n';

    std::cout << "\n\n";
}

#include <memory>

int main() {

    SharedPtr<int> ptr(new int(10));
    SharedPtr<int> ptr1(new int(25));

    ptr1 = ptr;

    printSharedPtrInfo(ptr);
    printSharedPtrInfo(ptr1);


}

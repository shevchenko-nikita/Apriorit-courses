#include <iostream>
#include "ForwardList.h"


template<typename T>
void printForwardList(const ForwardList<T> lst) {
    std::cout << "Size " << lst.size() << std::endl;
    for(auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << ' ';
    }
}

int main() {


    ForwardList<int> lst = {1, 2, 3, 4, 5, 6};

    auto it = lst.begin();
    ++it;
    ++it;

    lst.erase_after(it);

    printForwardList(lst);
}

#pragma once

#include <memory>

template<typename T>
class Node {
public:
    explicit Node(const T& new_val) : value(new_val) {}
    explicit Node(T&& other) : value(std::move(other)) {}

private:
    T value;
    std::shared_ptr<Node> next_node = nullptr;

    template<typename Resource>
    friend class ForwardList;

    template<typename Resource>
    friend class Iterator;
};


#pragma once

#include "Node.h"

template<typename T>
class Iterator {
private:
    std::shared_ptr<Node<T>> cur = nullptr;
public:
    Iterator() = default;
    Iterator(const std::shared_ptr<Node<T>> other) : cur(other) {}

    std::shared_ptr<Node<T>> get() const;

    T& operator*();
    const T& operator*() const;
    std::shared_ptr<Node<T>> operator++();

    bool operator==(const Iterator& other);
    bool operator!=(const Iterator& other);

    template<typename Resource>
    friend class ForwardLost;
};

template<typename T>
std::shared_ptr<Node<T>> Iterator<T>::get() const {
    return cur;
}

template<typename T>
T& Iterator<T>::operator*() {
    return cur->value;
}

template<typename T>
const T& Iterator<T>::operator*() const {
    return cur->value;
}

template<typename T>
std::shared_ptr<Node<T>> Iterator<T>::operator++() {
    cur = cur->next_node;
    return cur;
}

template<typename T>
bool Iterator<T>::operator==(const Iterator<T>& other) {
    return cur == other.cur;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other) {
    return cur != other.cur;
}
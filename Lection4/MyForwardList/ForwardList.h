#pragma once

#include <initializer_list>
#include <iostream>
#include "Node.h"

template<typename T>
class ForwardList {
public:
    ForwardList() = default;
    ForwardList(size_t count, const T& value);
    ForwardList(const ForwardList& other);
    ForwardList(ForwardList&& other) noexcept;
    ForwardList(std::initializer_list<T> init);

    ForwardList& operator=(const ForwardList& other);
    ForwardList& operator=(ForwardList&& other);

    ~ForwardList() = default;

    void push_front(const T& value);
    void push_front(T&& value);

    void pop_front();

    size_t size() const;


    class Iterator;

    Iterator begin();
    Iterator end();

    const Iterator begin() const;
    const Iterator end() const;

private:
    size_t list_size = 0;
    std::shared_ptr<Node<T>> head = nullptr;

};

template<typename T>
class ForwardList<T>::Iterator {
private:
    std::shared_ptr<Node<T>> cur = nullptr;
public:
    Iterator() = default;
    Iterator(const std::shared_ptr<Node<T>> other) : cur(other) {}

    T& operator*() const;
    std::shared_ptr<Node<T>> operator++();

    bool operator==(const Iterator& other);
    bool operator!=(const Iterator& other);
};

template<typename T>
T& ForwardList<T>::Iterator::operator*() const {
    return cur->value;
}

template<typename T>
std::shared_ptr<Node<T>> ForwardList<T>::Iterator::operator++() {
    cur = cur->next_node;
    return cur;
}

template<typename T>
bool ForwardList<T>::Iterator::operator==(const Iterator& other) {
    return cur == other.cur;
}

template<typename T>
bool ForwardList<T>::Iterator::operator!=(const Iterator& other) {
    return cur != other.cur;
}

template<typename T>
ForwardList<T>::ForwardList(size_t count, const T& value) : list_size(count) {
    while(count--) {
        push_front(value);
    }
}

template<typename T>
ForwardList<T>::ForwardList(const ForwardList& other) : list_size(other.list_size) { /// !!!!!!!!!!
    std::shared_ptr<Node<T>> cur_node = nullptr;
    std::shared_ptr<Node<T>> prev_node = nullptr;

    for(const auto& other_node : other) {
        cur_node = std::make_shared<Node<T>>(Node<T>(*other_node));

        if(head == nullptr) {
            head = cur_node;
        }
        else {
            prev_node->next_node = cur_node;
        }
        prev_node = cur_node;
    }
}

template<typename T>
ForwardList<T>::ForwardList(ForwardList&& other) noexcept : head(other.head), list_size(other.list_size) {
    other.head = nullptr;
    other.list_size = 0;
}

template<typename T>
ForwardList<T>::ForwardList(std::initializer_list<T> init) {
    for(auto value = std::rbegin(init); value != std::rend(init); ++value) {
        push_front(*value);
    }
}

template<typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList& other) {
    list_size = other.list_size;
    head = nullptr;

    std::shared_ptr<Node<T>> cur_node = nullptr;
    std::shared_ptr<Node<T>> prev_node = nullptr;

    for(Iterator other_node = other.begin(); other_node != other.end(); ++other_node) {
        cur_node = std::make_shared<Node<T>>(Node<T>(*other_node));
        if(head == nullptr) {
            head = cur_node;
        }
        else {
            prev_node->next_node = cur_node;
        }
        prev_node = cur_node;
    }

    return *this;
}

template<typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList&& other) {
    list_size = other.list_size;
    head = other.head;

    other.head = nullptr;
    other.list_size = 0;

    return *this;
}

template<typename T>
void ForwardList<T>::push_front(const T& value) {
    auto new_node = std::make_shared<Node<T>>(Node<T>(value));
    new_node->next_node = head;

    head = new_node;
    ++list_size;
}

template<typename T>
void ForwardList<T>::push_front(T&& value) {
    auto new_node = std::make_shared<Node<T>>(Node<T>(std::move(value)));
    new_node->next_node = head;

    head = new_node;
    ++list_size;
}

template<typename T>
void ForwardList<T>::pop_front() {
    if(head) {
        head = head->next_node;
        --list_size;
    }
}

template<typename T>
size_t ForwardList<T>::size() const {
    return list_size;
}

template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::begin() {
    return Iterator(head);
}

template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::end() {
    return Iterator();
}

template<typename T>
const typename ForwardList<T>::Iterator ForwardList<T>::begin() const {
    return Iterator(head);
}

template<typename T>
const typename ForwardList<T>::Iterator ForwardList<T>::end() const {
    return Iterator();
}
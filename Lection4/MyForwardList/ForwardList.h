#pragma once

#include <initializer_list>
#include <iostream>

#include "Node.h"
#include "Iterator.h"

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

    void erase_after(const Iterator<T> pos);

    void clear();

    size_t size() const;

    Iterator<T> begin();
    Iterator<T> end();

    const Iterator<T> begin() const;
    const Iterator<T> end() const;

private:
    void copy(const ForwardList& other);

    size_t list_size = 0;
    std::shared_ptr<Node<T>> head = nullptr;

};

template<typename T>
ForwardList<T>::ForwardList(size_t count, const T& value) : list_size(count) {
    while(count--) {
        push_front(value);
    }
}

template<typename T>
ForwardList<T>::ForwardList(const ForwardList& other) {
    copy(other);
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
    head.reset();

    copy(other);

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
void ForwardList<T>::erase_after(const Iterator<T> pos) {
    if(pos.get() == nullptr) {
        return;
    }

    auto cur_node = pos.get();
    auto next_node = cur_node->next_node;

    if(next_node) {
        auto new_next_node = next_node->next_node;
        cur_node->next_node = new_next_node;

        next_node.reset();
        --list_size;
    }

}

template<typename T>
void ForwardList<T>::clear() {
    list_size = 0;
    head.reset();
}

template<typename T>
size_t ForwardList<T>::size() const {
    return list_size;
}

template<typename T>
Iterator<T> ForwardList<T>::begin() {
    return Iterator<T>(head);
}

template<typename T>
Iterator<T> ForwardList<T>::end() {
    return Iterator<T>();
}

template<typename T>
const Iterator<T> ForwardList<T>::begin() const {
    return Iterator<T>(head);
}

template<typename T>
const Iterator<T> ForwardList<T>::end() const {
    return Iterator<T>();
}

template<typename T>
void ForwardList<T>::copy(const ForwardList<T> &other) {
    list_size = other.list_size;

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
}
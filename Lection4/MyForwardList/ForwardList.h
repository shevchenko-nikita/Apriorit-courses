#pragma once

#include <memory>
#include <initializer_list>

template<typename T>
class ForwardList {
public:
    ForwardList() = default;
    ForwardList(size_t count, const T& value);
    ForwardList(const ForwardList& other);
    ForwardList(ForwardList&& other);
    ForwardList(std::initializer_list<T> init);

    ForwardList& operator=(const ForwardList& other);
    ForwardList& operator=(ForwardList&& other);

    ~ForwardList();

    void push_front(const T& value);
    void push_front(T&& value);

    size_t size() const;

private:

    class Node {
        T value;
        Node* next_node = nullptr;
    };

    Node* head = nullptr;
    size_t list_size = 0;
};
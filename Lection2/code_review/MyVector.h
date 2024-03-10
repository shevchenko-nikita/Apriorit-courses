#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>

/*
 * MyVector stores a collection of objects with their names.
 *
 * For each object T, MyVector stores T`s name as std::string.
 * Several objects can have similar name.
 * operator[](const std::string& name) should return the first object
 * with the given name.
 *
 * Your task is to find as many mistakes and drawbacks in this code
 * (according to the presentation) as you can.
 * Annotate these mistakes with comments.
 *
 * Once you have found all the mistakes, rewrite the code
 * so it would not change its original purpose
 * and it would contain no mistakes.
 * Try to make the code more efficient without premature optimization.
 *
 * You can change MyVector interface completely, but there are several rules:
 * 1) you should correctly and fully implement copy-on-write idiom.
 * 2) std::pair<const T&, const std::string&> operator[](int index) const must take constant time at worst.
 * 3) const T& operator[](const std::string& name) const should be present.
 * 4) both operator[] should have non-const version.
 * 5) your implementation should provide all the member types of std::vector.
 * 6) your implementation should provide the following functions:
 *    1) begin(), cbegin(), end(), cend()
 *    2) empty(), size()
 *    3) reserve(), clear()
 */

template <typename T>
class MyVector : public std::vector<T>
{
public:
    MyVector()
            : m_names(std::make_shared<std::vector<std::string>>(std::vector<std::string>()))
    {

    }

    MyVector(const MyVector& other)
            : std::vector<T>(other),
              m_names(other.m_names)
    {

    }

    ~MyVector() = default;

    void push_back(const T& obj, const std::string& name);

    std::pair<const T&, const std::string&> operator[](int index) const;
    std::pair<T&, std::string&> operator[](int index);

    const T& operator[](const std::string& name) const;
    T& operator[](const std::string& name);

    std::vector<std::string>::iterator names_begin();
    std::vector<std::string>::const_iterator names_begin() const;

    std::vector<std::string>::iterator names_end();
    std::vector<std::string>::const_iterator names_end() const;

    std::vector<std::string>::const_iterator names_cbegin() const;

    std::vector<std::string>::const_iterator names_cend() const;

    size_t size() const;

    bool empty() const;

    void reserve(size_t len);

    void clear();

private:
    void copy_names();

private:
    std::shared_ptr<std::vector<std::string>> m_names;

};


template<typename T>
void MyVector<T>::push_back(const T& obj, const std::string& name) {
    copy_names();

    std::vector<T>::push_back(obj);
    m_names->push_back(name);
}

template<typename T>
std::pair<const T&, const std::string&> MyVector<T>::operator[](int index) const {
    return std::make_pair(std::vector<T>::at(index), m_names->at(index));
}

template<typename T>
std::pair<T&, std::string&> MyVector<T>::operator[](int index) {
    return std::make_pair(std::vector<T>::at(index), m_names->at(index));
}

template<typename T>
const T& MyVector<T>::operator[](const std::string& name) const {
    const auto& iter = std::find(m_names->begin(), m_names->end(), name);
    if (iter == m_names->end()) {
        throw std::invalid_argument(name + " is not found in the MyVector");
    }

    return std::vector<T>::operator[](std::distance(m_names->begin(), iter));
}

template<typename T>
T& MyVector<T>::operator[](const std::string& name) {
    const auto& iter = std::find(m_names->begin(), m_names->end(), name);
    if (iter == m_names->end()) {
        throw std::invalid_argument(name + " is not found in the MyVector");
    }

    return std::vector<T>::operator[](std::distance(m_names->begin(), iter));
}

template<typename T>
std::vector<std::string>::iterator MyVector<T>::names_begin() {
    return m_names->begin();
}

template<typename T>
std::vector<std::string>::const_iterator MyVector<T>::names_begin() const {
    return m_names->begin();
}

template<typename T>
std::vector<std::string>::iterator MyVector<T>::names_end() {
    return m_names->end();
}

template<typename T>
std::vector<std::string>::const_iterator MyVector<T>::names_end() const {
    return m_names->end();
}

template<typename T>
std::vector<std::string>::const_iterator MyVector<T>::names_cbegin() const {
    return m_names->cbegin();
}

template<typename T>
std::vector<std::string>::const_iterator MyVector<T>::names_cend() const {
    return m_names->cend();
}

template<typename T>
void MyVector<T>::reserve(size_t len) {
    copy_names();

    std::vector<T>::reserve(len);
    m_names->reserve(len);
}

template<typename T>
void MyVector<T>::clear() {
    copy_names();

    std::vector<T>::clear();
    m_names->clear();
}

template<typename T>
size_t MyVector<T>::size() const {
    return m_names->size();
}

template<typename T>
bool MyVector<T>::empty() const {
    return std::vector<T>::empty() && m_names->empty();
}

template<typename T>
void MyVector<T>::copy_names() {
    if(m_names.use_count() > 1) {
        m_names = std::make_shared<std::vector<std::string>>(*m_names);
    }
}


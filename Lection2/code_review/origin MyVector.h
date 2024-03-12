// It's better to use #pragma once
#ifndef CODEREVIEWTASK_MYVECTOR_HPP
#define CODEREVIEWTASK_MYVECTOR_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>


template <typename T>
class MyVector : public std::vector<T>
{
public:
    // It's better to use an initializer list
    // than assigment in constructor's body
    MyVector()
    {
        // Instead of these code, better to use smart pointer - shared_ptr
        m_ref_ptr = new size_t(1);
        m_names = new std::vector<std::string>();
    }

    // Use shared_ptr as noticed above
    MyVector(const MyVector& other)
            : std::vector<T>(other),
              m_ref_ptr(other.m_ref_ptr),
              m_names(other.m_names)
    {
        (*m_ref_ptr)++;
    }

    // Use shared_ptr as noticed above
    ~MyVector()
    {
        if (--*m_ref_ptr == 0)
        {
            delete m_ref_ptr;
            delete m_names;
        }
    }

    void push_back(const T& obj, const std::string& name)
    {
        copy_names();

        std::vector<T>::push_back(obj);
        m_names->push_back(name);
    }

    std::pair<const T&, const std::string&> operator[](int index) const
    {
        // I think there is also need to check that index is not lower than 0
        if (index >= std::vector<T>::size())
        {
            // There is better to use throw without operator new.
            throw new std::out_of_range("Index is out of range");
        }

        // Use method 'at(id)' that return value in constant time
        // and if id is out of range it will be throw an exception std::out_of_range
        return std::pair<const T&, const std::string&>(std::vector<T>::operator[](index), (*m_names)[index]);
    }

    const T& operator[](const std::string& name) const
    {
        // Use auto to make this row more readable
        std::vector<std::string>::const_iterator iter = std::find(m_names->begin(), m_names->end(), name);
        if (iter == m_names->end())
        {
            // As mentioned earlier, there is better to use without operator new
            throw new std::invalid_argument(name + " is not found in the MyVector");
        }

        // Use distance to make increase readability
        return std::vector<T>::operator[](iter - m_names->begin());
    }

private:
    void copy_names()
    {
        if (*m_ref_ptr == 1)
        {
            return;
        }

        // use shared_ptr and function make_shared
        size_t* temp_ref_ptr = new size_t(1);
        std::vector<std::string>* temp_names = new std::vector<std::string>(*m_names);

        (*m_ref_ptr)--;
        m_ref_ptr = temp_ref_ptr;
        m_names = temp_names;
    }

private:
    // Use shared_ptr for m_names
    std::vector<std::string>* m_names;
    size_t* m_ref_ptr;
};


#endif



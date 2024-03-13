#pragma once

#include "SharedPtr.h"
#include "ControlBlock.h"

template<typename Resource>
class WeakPtr
{
public:
    WeakPtr() = default;
    WeakPtr(const WeakPtr<Resource>& rhs);
    WeakPtr(const SharedPtr<Resource>& rhs);
    WeakPtr<Resource>& operator=(const WeakPtr<Resource>& rhs);
    WeakPtr<Resource>& operator=(const SharedPtr<Resource>& rhs);
    ~WeakPtr();

    void Reset();
    void Swap(WeakPtr<Resource>& rhs);
    long UseCount() const;
    bool Expired() const;
    SharedPtr<Resource> Lock() const;

private:
    template<typename T>
    friend class SharedPtr;

private:
    ControlBlock<Resource>* control_block = nullptr;
};

template<typename Resource>
WeakPtr<Resource>::WeakPtr(const WeakPtr<Resource>& rhs)
                          : control_block(rhs.control_block)
{
    if(control_block) {
        control_block->appendWeaks();
    }
}

template<typename Resource>
WeakPtr<Resource>::WeakPtr(const SharedPtr<Resource>& rhs)
        : control_block(rhs.control_block)
{
    if(control_block) {
        control_block->appendWeaks();
    }
}

template<typename Resource>
WeakPtr<Resource>& WeakPtr<Resource>::operator=(const WeakPtr<Resource>& rhs) {
    if(control_block != rhs.control_block) {
        Reset();
        control_block = rhs.control_block;

        if(control_block) {
            control_block->appendWeaks();
        }
    }
    return *this;
}

template<typename Resource>
WeakPtr<Resource>& WeakPtr<Resource>::operator=(const SharedPtr<Resource>& rhs) {
    if(control_block != rhs.control_block) {
        Reset();
        control_block = rhs.control_block;

        if(control_block) {
            control_block->appendWeaks();
        }
    }
    return *this;
}

template<typename Resource>
WeakPtr<Resource>::~WeakPtr() {
    Reset();
}

template<typename Resource>
void WeakPtr<Resource>::Reset() {
    if(control_block) {
        control_block->subtractWeaks();

        if(control_block->getWeaksCount() == 0 &&
           control_block->getRefsCount() == 0)
        {
            delete control_block;
        }

        control_block = nullptr;
    }
}

template<typename Resource>
void WeakPtr<Resource>::Swap(WeakPtr<Resource>& rhs) {
    std::swap(control_block, rhs.control_block);
}

template<typename Resource>
long WeakPtr<Resource>::UseCount() const {
    if(control_block == nullptr) {
        return 0;
    }

    return control_block->getRefsCount();
}

template<typename Resource>
bool WeakPtr<Resource>::Expired() const {
    return UseCount() == 0;
}

template<typename Resource>
SharedPtr<Resource> WeakPtr<Resource>::Lock() const {
    if(Expired()) {
        return SharedPtr<Resource>();
    }

    return SharedPtr<Resource>(*this);
}
#pragma once

#include "ControlBlock.h"

//#include "WeakPtr.h"

template <typename Resource>
class WeakPtr;

template <typename Resource>
class SharedPtr
{
public:
    SharedPtr() = default;
    explicit SharedPtr(Resource* res);
    SharedPtr(const SharedPtr<Resource>& rhs);
    SharedPtr(const WeakPtr<Resource>& rhs);
    SharedPtr<Resource>& operator=(const SharedPtr<Resource>& rhs);
    ~SharedPtr();

    void Reset();
    void Reset(Resource* res);
    void Swap(SharedPtr<Resource>& rhs);

    Resource* Get() const;
    Resource& operator*() const;
    Resource* operator->() const;
    long UseCount() const;

private:
    template<typename T>
    friend class WeakPtr;

private:
    ControlBlock<Resource>* control_block = nullptr;
};

template<typename Resource>
SharedPtr<Resource>::SharedPtr(Resource *res)
                              : control_block(new ControlBlock(res))
{

}

template<typename Resource>
SharedPtr<Resource>::SharedPtr(const SharedPtr<Resource>& rhs)
                              : control_block(rhs.control_block)
{
    if(control_block) {
        control_block->appendRefs();
    }
}

template<typename Resource>
SharedPtr<Resource>::SharedPtr(const WeakPtr<Resource>& rhs)
                              : control_block(rhs.control_block)
{
    if(control_block) {
        control_block->appendRefs();
    }
}

template<typename Resource>
SharedPtr<Resource>& SharedPtr<Resource>::operator=(const SharedPtr<Resource>& rhs) {
    if(control_block != rhs.control_block) {
        Reset();
        control_block = rhs.control_block;

        if (control_block) {
            control_block->appendRefs();
        }
    }

    return *this;
}

template<typename Resource>
SharedPtr<Resource>::~SharedPtr() {
    Reset();
}

template<typename Resource>
void SharedPtr<Resource>::Reset() {
    if(control_block) {
        control_block->subtractRefs();

        if(control_block->getRefsCount() == 0 &&
           control_block->getWeaksCount() == 0)
        {
            delete control_block;
        }

        control_block = nullptr;
    }
}

template<typename Resource>
void SharedPtr<Resource>::Reset(Resource* res) {
    Reset();
    control_block = new ControlBlock(res);
}

template<typename Resource>
void SharedPtr<Resource>::Swap(SharedPtr<Resource>& rhs) {
    std::swap(control_block, rhs.control_block);
}

template<typename Resource>
Resource* SharedPtr<Resource>::Get() const {
    if(control_block == nullptr) {
        throw std::runtime_error("trying to accsess to nullptr");
    }
    return control_block->getPointer();
}

template<typename Resource>
Resource& SharedPtr<Resource>::operator*() const {
    if(control_block == nullptr) {
        throw std::runtime_error("trying to accsess to nullptr");
    }
    return *control_block->getPointer();
}

template<typename Resource>
Resource* SharedPtr<Resource>::operator->() const {
    if(control_block == nullptr) {
        throw std::runtime_error("trying to accsess to nullptr");
    }
    return control_block->getPointer();
}

template<typename Resource>
long SharedPtr<Resource>::UseCount() const {
    if(control_block == nullptr) {
        return 0;
    }

    return control_block->getRefsCount();
}
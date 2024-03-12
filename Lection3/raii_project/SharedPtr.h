#pragma once

#include "ControlBlock.h"

template <typename Resource>
class SharedPtr
{
public:
    SharedPtr();
    explicit SharedPtr(Resource* res);
    SharedPtr(const SharedPtr<Resource>& rhs);
//    SharedPtr(const WeakPtr<Resource>& rhs);
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
    ControlBlock<Resource>* control_block = nullptr;
};


template<typename Resource>
SharedPtr<Resource>::SharedPtr() : control_block(new ControlBlock<Resource>())
{

}

template<typename Resource>
SharedPtr<Resource>::SharedPtr(Resource *res)
                              : control_block(new ControlBlock(res))
{

}

template<typename Resource>
SharedPtr<Resource>::SharedPtr(const SharedPtr<Resource>& rhs)
                              : control_block(rhs.control_block)
{
    control_block->Append();
}

template<typename Resource>
SharedPtr<Resource>& SharedPtr<Resource>::operator=(const SharedPtr<Resource>& rhs) {
    delete control_block;
    control_block = rhs;
    control_block.Append();
}

template<typename Resource>
SharedPtr<Resource>::~SharedPtr() {
    delete control_block;
}

template<typename Resource>
SharedPtr<Resource>::Resource* Get() const {
    return
}

template<typename Resource>
SharedPtr<Resource>::Resource& operator*() const;

template<typename Resource>
SharedPtr<Resource>::Resource* operator->() const;

template<typename Resource>
SharedPtr<Resource>::long UseCount() const;
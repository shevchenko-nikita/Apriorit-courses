#pragma once

template<typename Resource>
class ControlBlock {
public:
    ControlBlock() = default;
    ControlBlock(Resource* res);

    ~ControlBlock();

    void Append();
    void Subtract();

    int getRefsCount() const;

    Resource* getPointer() const;

private:
    int refs_count = 0;
    Resource* value = nullptr;

};

template<typename Resource>
ControlBlock<Resource>::ControlBlock(Resource* res)
            : value(res), refs_count(1)
{

}

template<typename Resource>
ControlBlock<Resource>::~ControlBlock() {
    Subtract();
}

template<typename Resource>
void ControlBlock<Resource>::Append() {
    ++refs_count;
}

template<typename Resource>
void ControlBlock<Resource>::Subtract() {
    if(value != nullptr) {
        --refs_count;
        if (refs_count == 0) {
            delete value;
        }
    }
}

template<typename Resource>
int ControlBlock<Resource>::getRefsCount() const {
    return refs_count;
}

template<typename Resource>
Resource* ControlBlock<Resource>::getPointer() const {
    return value;
}
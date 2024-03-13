#pragma once

template<typename Resource>
class ControlBlock {
public:
    explicit ControlBlock(Resource* res);

    ~ControlBlock();

    void appendRefs();
    void subtractRefs();

    void appendWeaks();
    void subtractWeaks();

    int getRefsCount() const;
    int getWeaksCount() const;

    Resource* getPointer() const;

private:
    int refs_count;
    int weaks_count;
    Resource* value;

};

template<typename Resource>
ControlBlock<Resource>::ControlBlock(Resource* res)
                                    : value(res),
                                      refs_count(1),
                                      weaks_count(0)
{

}

template<typename Resource>
ControlBlock<Resource>::~ControlBlock() {
    if(value) {
        delete value;
    }
}

template<typename Resource>
void ControlBlock<Resource>::appendRefs() {
    ++refs_count;
}

template<typename Resource>
void ControlBlock<Resource>::subtractRefs() {
    --refs_count;
    if(refs_count == 0 && value) {
        delete value;
        value = nullptr;
    }
}

template<typename Resource>
void ControlBlock<Resource>::appendWeaks() {
    ++weaks_count;
}

template<typename Resource>
void ControlBlock<Resource>::subtractWeaks() {
    --weaks_count;
}

template<typename Resource>
int ControlBlock<Resource>::getRefsCount() const {
    return refs_count;
}

template<typename Resource>
int ControlBlock<Resource>::getWeaksCount() const {
    return weaks_count;
}

template<typename Resource>
Resource* ControlBlock<Resource>::getPointer() const {
    return value;
}
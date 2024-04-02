#include "counter.h"

Counter::Counter(int startValue) : m_count(startValue) {

}

int Counter::Increment() {
    ++m_count;
    emit IncrementEmit();
    return m_count;
}

int Counter::Decrement() {
    --m_count;
    emit DecrementEmit();
    return m_count;
}

void Counter::IncrementSlot() {
    ++m_count;
}

void Counter::DecrementSlot() {
    --m_count;
}

int Counter::GetValue() {
    return m_count;
}

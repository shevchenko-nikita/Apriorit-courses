#pragma once

#include <QObject>

class Counter : public QObject {
    Q_OBJECT
public:
    Counter() = default;
    Counter(int startValue);

    int Increment();
    int Decrement();

    int GetValue();

signals:
    void IncrementEmit();
    void DecrementEmit();

public slots:
    void IncrementSlot();
    void DecrementSlot();

private:
    int m_count;
};

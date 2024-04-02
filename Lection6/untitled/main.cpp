#include <QCoreApplication>

#include <iostream>

#include "counter.h"

void printCountersValue(Counter& counter1, Counter& counter2) {
    std::cout << counter1.GetValue() << ' ' << counter2.GetValue() << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Counter counter1(5);
    Counter counter2(10);

    QObject::connect(&counter1, SIGNAL(IncrementEmit()), &counter2, SLOT(IncrementSlot()));
    QObject::connect(&counter1, SIGNAL(DecrementEmit()), &counter2, SLOT(DecrementSlot()));

    QObject::connect(&counter2, SIGNAL(IncrementEmit()), &counter1, SLOT(IncrementSlot()));
    QObject::connect(&counter2, SIGNAL(DecrementEmit()), &counter1, SLOT(DecrementSlot()));

    printCountersValue(counter1, counter2);

    counter1.Increment();

    printCountersValue(counter1, counter2);

    counter2.Increment();

    printCountersValue(counter1, counter2);

    counter1.Decrement();

    printCountersValue(counter1, counter2);

    counter2.Decrement();

    printCountersValue(counter1, counter2);

    return a.exec();
}

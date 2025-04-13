#ifndef COUNTER_H
#define COUNTER_H

#include <memory>
#include <functional>
#include "Mutex.h"

class Counter {
public:
    Counter(bool protect);
    void increment();
    double value() const;

private:
    double m_value = 0.0;
    std::unique_ptr<Mutex> p_mutex;
    std::function<void()> incrementFunction;

    void incrProtect();
    void incrNoProtect();
};

#endif

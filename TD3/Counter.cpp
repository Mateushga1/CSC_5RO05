#include "Counter.h"

Counter::Counter(bool protect) {
    if (protect) {
        p_mutex = std::make_unique<Mutex>();
        incrementFunction = [this]() { incrProtect(); };
    } else {
        incrementFunction = [this]() { incrNoProtect(); };
    }
}

void Counter::increment() {
    incrementFunction();
}

double Counter::value() const {
    return m_value;
}

void Counter::incrProtect() {
    Mutex::Lock lock(*p_mutex);
    m_value += 1.0;
}

void Counter::incrNoProtect() {
    m_value += 1.0;
}

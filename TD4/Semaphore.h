#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "Monitor.h"
#include <limits>
#include <stdexcept>

using CountType = unsigned long;

class Semaphore
{
public:
    Semaphore(CountType initValue = 0, CountType maxValue = std::numeric_limits<CountType>::max());
    void give();
    void take();
    bool take(long timeout_ms);
    CountType getCurrentCount() const;

private:
    CountType counter;
    CountType maxCount;
    Mutex mutex;
    Monitor monitor;
    Monitor::Lock lock;
    pthread_cond_t notEmpty;
};
#endif

#include "Semaphore.h"
#include "Timespec.h"

Semaphore::Semaphore(CountType initValue, CountType maxValue)
    : mutex(), monitor(mutex), counter(initValue), maxCount(maxValue), lock(monitor)
{
    if (initValue > maxValue)
        throw std::invalid_argument("initValue cannot exceed maxValue");
    if (maxValue == 0)
        throw std::invalid_argument("maxValue must be at least 1");
    pthread_cond_init(&notEmpty, nullptr);
}

void Semaphore::give()
{
    Monitor::Lock guard(monitor);
    if (counter < maxCount)
    {
        counter++;
        monitor.notifyAll();
    }
}

void Semaphore::take()
{
    Monitor::Lock guard(monitor);
    while (counter == 0)
    {
        guard.wait();
    }
    counter--;
}

bool Semaphore::take(long timeout_ms) {
    Monitor::Lock guard(monitor);
    if (counter == 0) {
        timespec abstime = timespec_now() + timespec_from_ms(timeout_ms);
        int result = pthread_cond_timedwait(
            &notEmpty,
            mutex.getPosixMutex(), 
            &abstime
        );
        if (result == ETIMEDOUT || counter == 0) {
            return false;
        }
    }
    counter--;
    return true;
}

CountType Semaphore::getCurrentCount() const
{
    return counter;
}

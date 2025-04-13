#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>
#include "Timespec.h"
#include "TimeoutException.h"

class Mutex
{
public:
    Mutex(bool isInversionSafe = false);
    ~Mutex();

    class Lock
    {
    public:
        Lock(Mutex &mutex);
        Lock(Mutex &mutex, double timeout_ms);
        ~Lock();

    private:
        Mutex &mutex;
    };

private:
    pthread_mutex_t posixMutexId;
    pthread_mutexattr_t posixMutexAttrId;
    void lock();
    bool lock(double timeout_ms);
    void unlock();
    bool isInversionSafe;
};

#endif

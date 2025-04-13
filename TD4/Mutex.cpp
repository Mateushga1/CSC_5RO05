#include "Mutex.h"
#include <stdexcept>

Mutex::Mutex(bool isInversionSafe) : isInversionSafe(isInversionSafe)
{
    if (isInversionSafe)
    {
        pthread_mutexattr_init(&posixMutexAttrId);
        pthread_mutexattr_settype(&posixMutexAttrId, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutexattr_setprotocol(&posixMutexAttrId, PTHREAD_PRIO_INHERIT);
        pthread_mutex_init(&posixMutexId, &posixMutexAttrId);
    }
    else
    {
        pthread_mutex_init(&posixMutexId, nullptr);
    }
}

Mutex::~Mutex()
{
    if (isInversionSafe)
    {
        pthread_mutexattr_destroy(&posixMutexAttrId);
    }
    pthread_mutex_destroy(&posixMutexId);
}

pthread_mutex_t* Mutex::getPosixMutex() {
    return &posixMutexId;
}

void Mutex::lock()
{
    pthread_mutex_lock(&posixMutexId);
}

bool Mutex::lock(double timeout_ms)
{
    timespec now = timespec_now();
    timespec timeout = timespec_from_ms(timeout_ms);
    timespec absolute_time = now + timeout;
    return pthread_mutex_timedlock(&posixMutexId, &absolute_time) == 0;
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&posixMutexId);
}

Mutex::Lock::Lock(Mutex &mutex) : mutex(mutex)
{
    mutex.lock();
}

Mutex::Lock::Lock(Mutex &mutex, double timeout_ms) : mutex(mutex)
{
    if (!mutex.lock(timeout_ms))
    {
        throw TimeoutException(static_cast<long>(timeout_ms));
    }
}

Mutex::Lock::~Lock()
{
    mutex.unlock();
}

#include "Monitor.h"

Monitor::Monitor(Mutex &mutex) : mutexRef(mutex)
{
    pthread_cond_init(&posixCondId, nullptr);
}

Monitor::~Monitor()
{
    pthread_cond_destroy(&posixCondId);
}

void Monitor::notify()
{
    pthread_cond_signal(&posixCondId);
}

void Monitor::notifyAll()
{
    pthread_cond_broadcast(&posixCondId);
}

Monitor::Lock::Lock(Monitor &monitor)
    : Mutex::Lock(monitor.mutexRef), monitorRef(monitor) {}

Monitor::Lock::Lock(Monitor &monitor, long timeout_ms)
    : Mutex::Lock(monitor.mutexRef, timeout_ms), monitorRef(monitor) {}

void Monitor::Lock::wait()
{
    pthread_cond_wait(
        &monitorRef.posixCondId,
        monitorRef.mutexRef.getPosixMutex());
}

void Monitor::Lock::wait(long timeout_ms)
{
    timespec abstime = timespec_now() + timespec_from_ms(timeout_ms);
    pthread_cond_timedwait(
        &monitorRef.posixCondId,
        monitorRef.mutexRef.getPosixMutex(),
        &abstime);
}

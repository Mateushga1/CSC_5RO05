#ifndef MONITOR_H
#define MONITOR_H

#include "Mutex.h"
#include "Timespec.h"
#include <pthread.h>

class Monitor
{
public:
    class Lock : public Mutex::Lock
    {
    public:
        Lock(Monitor &monitor);
        Lock(Monitor &monitor, long timeout_ms);
        void wait();
        void wait(long timeout_ms);

    private:
        Monitor &monitorRef;
    };

    explicit Monitor(Mutex &mutex);
    ~Monitor();
    void notify();
    void notifyAll();

private:
    pthread_cond_t posixCondId;
    Mutex &mutexRef;
};

#endif

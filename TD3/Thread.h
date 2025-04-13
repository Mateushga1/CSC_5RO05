#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include "Chrono.h"

class Thread {
public:
    const int id;

    Thread(int id);
    virtual ~Thread();

    void start(int priority = 0);
    void join();
    bool isStarted() const;
    long duration_ms() const;

    static int getMaxPrio(int policy);
    static int getMinPrio(int policy);
    static void setMainSched(int policy);
    static int getMainSched(int policy);

private:
    pthread_t posixThreadId;
    pthread_attr_t posixThreadAttrId;
    Chrono chrono;
    bool started = false;

    static void* call_run(void* v_thread);

protected:
    virtual void run() = 0;
};

#endif

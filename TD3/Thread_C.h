#ifndef THREAD_C_H
#define THREAD_C_H

#include "Thread.h"
#include "CpuLoop.h"
#include "Mutex.h"

class Thread_C : public Thread {
public:
    Thread_C(int id, CpuLoop& cpuLoop, Mutex& resource);
    void run() override;

private:
    CpuLoop& cpuLoop;
    Mutex& resource;
    const int execTimeMs = 5000;
    const int accessRTimeMs = 2000;
    const int holdRTimeMs = 2000;     
};

#endif

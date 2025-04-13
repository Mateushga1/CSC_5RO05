#ifndef THREAD_A_H
#define THREAD_A_H

#include "Thread.h"
#include "CpuLoop.h"
#include "Mutex.h"

class Thread_A : public Thread {
public:
    Thread_A(int id, CpuLoop& cpuLoop, Mutex& resource);
    void run() override;

private:
    CpuLoop& cpuLoop;
    Mutex& resource;
    const int activationTimeMs = 3000;
    const int execTimeMs = 4000;
    const int accessRTimeMs = 1000;
    const int holdRTimeMs = 1000;           
};

#endif

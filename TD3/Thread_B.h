#ifndef THREAD_B_H
#define THREAD_B_H

#include "Thread.h"
#include "CpuLoop.h"

class Thread_B : public Thread {
public:
    Thread_B(int id, CpuLoop& cpuLoop);
    void run() override;

private:
    CpuLoop& cpuLoop;
    const int activationTimeMs = 3000;
    const int execTimeMs = 1000;       
};

#endif

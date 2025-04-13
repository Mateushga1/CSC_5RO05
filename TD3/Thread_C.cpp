#include "Thread_C.h"

Thread_C::Thread_C(int id, CpuLoop& cpuLoop, Mutex& resource)
    : Thread(id), cpuLoop(cpuLoop), resource(resource) {}

void Thread_C::run() {
    cpuLoop.runTime(accessRTimeMs);

    {
        Mutex::Lock lock(resource);
        cpuLoop.runTime(holdRTimeMs);
    }

    cpuLoop.runTime(execTimeMs - accessRTimeMs - holdRTimeMs);
}

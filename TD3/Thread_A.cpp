#include "Thread_A.h"
#include "Chrono.h"

Thread_A::Thread_A(int id, CpuLoop& cpuLoop, Mutex& resource)
    : Thread(id), cpuLoop(cpuLoop), resource(resource) {}

void Thread_A::run() {
    Chrono activationChrono;
    while (activationChrono.lap_ms() < activationTimeMs) {
    }

    cpuLoop.runTime(accessRTimeMs);

    {
        Mutex::Lock lock(resource);
        cpuLoop.runTime(holdRTimeMs);
    }

    cpuLoop.runTime(execTimeMs - accessRTimeMs - holdRTimeMs);
}

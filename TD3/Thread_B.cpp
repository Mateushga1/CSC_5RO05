#include "Thread_B.h"
#include "Chrono.h"

Thread_B::Thread_B(int id, CpuLoop& cpuLoop)
    : Thread(id), cpuLoop(cpuLoop) {}

void Thread_B::run() {
    Chrono activationChrono;
    while (activationChrono.lap_ms() < activationTimeMs) {
    }

    cpuLoop.runTime(execTimeMs);
}

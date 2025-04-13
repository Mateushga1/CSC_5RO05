#ifndef CPU_LOOP_H
#define CPU_LOOP_H

#include "Calibrator.h"
#include "Looper.h"
#include "Chrono.h"

class CpuLoop {
public:
    CpuLoop(Calibrator& calibrator);

    double runTime(double duration_ms);

private:
    Calibrator& calibrator;
    Looper looper;
};

#endif

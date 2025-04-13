#include "CpuLoop.h"
#include <cmath>

CpuLoop::CpuLoop(Calibrator& calibrator)
    : calibrator(calibrator) {}

double CpuLoop::runTime(double duration_ms) {
    double nLoops = calibrator.nLoops(duration_ms);

    Chrono chrono;
    chrono.restart();
    looper.runLoop(nLoops);
    timespec duration = chrono.stop();

    double actualTime_ms = timespec_to_ms(duration);

    double relativeError = ((actualTime_ms - duration_ms) / duration_ms) * 100.0;

    return relativeError;
}

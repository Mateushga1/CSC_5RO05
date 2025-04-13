#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <vector>
#include <cfloat>
#include "Timer.h"
#include "Looper.h"

class Calibrator : public Timer
{
public:
    Calibrator(double samplingPeriod_ms, unsigned nSamples);
    double nLoops(double duration_ms);

protected:
    void callback() override;

private:
    double a, b;
    std::vector<double> samples;
    Looper looper;
    unsigned nSamples;
    double samplingPeriod_ms;
    unsigned currentSample = 0;
};

#endif

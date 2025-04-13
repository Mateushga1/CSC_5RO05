#include "Calibrator.h"
#include <iostream>

Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples)
    : Timer(), looper(), nSamples(nSamples), samplingPeriod_ms(samplingPeriod_ms), currentSample(0)
{
    samples.reserve(nSamples);
    start_ms(samplingPeriod_ms, true);
    looper.runLoop(DBL_MAX);
}

void Calibrator::callback()
{
    samples.push_back(looper.getSample());
    currentSample = samples.size();

    if (currentSample >= nSamples)
    {
        stop();
        looper.stopLoop();

        double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumX2 = 0.0;
        for (unsigned i = 0; i < nSamples; ++i)
        {
            double x = (i + 1) * samplingPeriod_ms;
            double y = samples[i];
            sumX += x;
            sumY += y;
            sumXY += x * y;
            sumX2 += x * x;
        }
        a = (nSamples * sumXY - sumX * sumY) / (nSamples * sumX2 - sumX * sumX);
        b = (sumY - a * sumX) / nSamples;
    }
}

double Calibrator::nLoops(double duration_ms)
{
    return a * duration_ms + b;
}

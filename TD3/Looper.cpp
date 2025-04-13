#include "Looper.h"

double Looper::runLoop(double nLoops)
{
    doStop = false;
    iLoop = 0.0;
    while (!doStop && iLoop < nLoops)
    {
        iLoop += 1.0;
    }
    return iLoop;
}

double Looper::getSample() const
{
    return iLoop;
}

double Looper::stopLoop()
{
    doStop = true;
    return iLoop;
}

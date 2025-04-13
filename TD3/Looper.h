#ifndef LOOPER_H
#define LOOPER_H
#include <cfloat>

class Looper
{
private:
    volatile bool doStop;
    volatile double iLoop;

public:
    double runLoop(double nLoops = DBL_MAX);
    double getSample() const;
    double stopLoop();
};

#endif

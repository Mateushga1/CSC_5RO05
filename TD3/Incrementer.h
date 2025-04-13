#ifndef INCREMENTER_H
#define INCREMENTER_H

#include "Thread.h"
#include "Counter.h"
#include "Chrono.h"

class Incrementer : public Thread {
public:
    Incrementer(int id, Counter& counter, double nLoops);
    void run() override;

private:
    Counter& r_counter;
    const double nLoops;
};

#endif

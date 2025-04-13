#include "Incrementer.h"

Incrementer::Incrementer(int id, Counter& counter, double nLoops)
    : Thread(id), r_counter(counter), nLoops(nLoops) {}

void Incrementer::run() {
    for (double i = 0; i < nLoops; ++i) {
        r_counter.increment();
    }
}

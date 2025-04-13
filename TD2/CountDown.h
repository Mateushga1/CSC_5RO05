#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include "Timer.h"
#include <iostream>

class CountDown : public Timer {
public:
    CountDown(int initialCount);
    ~CountDown() = default;

    int getSample() const;

protected:
    void callback() override;

private:
    int count;
};

#endif

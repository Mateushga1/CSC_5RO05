#include "CountDown.h"
#include "Timespec.h"

CountDown::CountDown(int initialCount) : count(initialCount) {
    start_ms(1000, true);
    std::cout << "Countdown: " << count << std::endl;
}

void CountDown::callback() {
    count--;
    std::cout << "Countdown: " << count << std::endl;
    if (count <= 0) {
        stop();
    }
}

int CountDown::getSample() const {
    return count;
}

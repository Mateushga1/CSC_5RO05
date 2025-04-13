#include "CountDown.h"
#include "Timespec.h"

int main() {
    CountDown countdown(5);

    timespec delay = timespec_from_ms(1000);
    while (countdown.getSample() > 0) {
        timespec_wait(delay);
    }

    return 0;
}

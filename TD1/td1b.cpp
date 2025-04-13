#include <iostream>
#include "Chrono.h"

int main()
{
    Chrono chrono;

    std::cout << "Timer started." << std::endl;

    timespec delay = {2, 0};
    timespec_wait(delay);

    std::cout << "Time elapsed: " << chrono.lap_ms() << " ms" << std::endl;

    timespec elapsed = chrono.stop();
    std::cout << "Timer stopped. Total time: " << timespec_to_ms(elapsed) << " ms" << std::endl;

    std::cout << "Time elapsed after stopping: " << chrono.lap_ms() << " ms" << std::endl;

    chrono.restart();
    std::cout << "Timer restarted." << std::endl;

    delay = {1, 0};
    timespec_wait(delay);

    std::cout << "Time elapsed after restarting: " << chrono.lap_ms() << " ms" << std::endl;

    return 0;
}

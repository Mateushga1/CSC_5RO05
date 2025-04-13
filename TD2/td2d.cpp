#include <iostream>
#include <iomanip>
#include "Calibrator.h"
#include "Chrono.h"
#include "Looper.h"

int main() {
    std::cout << "TD2d start" << std::endl;

    double samplingPeriod_ms = 200;
    unsigned nSamples = 10;

    Calibrator calibrator(samplingPeriod_ms, nSamples);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Testing calibration with different execution times:\n";
    std::cout << "-------------------------------------------------\n";
    std::cout << "Expected Time (s) | Measured Time (s)\n";
    std::cout << "-------------------------------------------------\n";

    for (double execTime = 0.5; execTime <= 10.0; execTime += 0.2) {

        double expectedLoops = calibrator.nLoops(execTime * 1000);

        Looper looper;
        Chrono chrono;

        chrono.restart();
        looper.runLoop(expectedLoops);
        timespec duration = chrono.stop();

        double measuredTime = timespec_to_ms(duration) / 1000.0;

        std::cout << std::setw(17) << execTime << " | " << std::setw(18) << measuredTime << "\n";
    }

    return 0;
}

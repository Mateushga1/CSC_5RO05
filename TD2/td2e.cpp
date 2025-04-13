#include <iostream>
#include <iomanip>
#include "CpuLoop.h"
#include "Calibrator.h"

int main() {
    Calibrator calibrator(200.0, 10);
    CpuLoop cpuLoop(calibrator);

    std::cout << "Testing CpuLoop relative error:\n";
    std::cout << "Desired Time (ms) | Relative Error (%)\n";
    std::cout << "---------------------------------------\n";

    for (double desiredTime_ms = 500.0; desiredTime_ms <= 10000.0; desiredTime_ms += 200.0) {
        double error = cpuLoop.runTime(desiredTime_ms);

        std::cout << std::fixed << std::setprecision(1);
        std::cout << std::setw(17) << desiredTime_ms << " | "
                  << std::setw(15) << std::setprecision(2) << error << "\n";
    }

    return 0;
}

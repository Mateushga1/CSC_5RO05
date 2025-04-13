#include <iostream>
#include <iomanip>
#include <string>
#include "Looper.h"
#include "Chrono.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <nLoops>" << std::endl;
        return 1;
    }

    double nLoops = std::stod(argv[1]); 

    Looper looper;
    Chrono chrono;

    chrono.restart();
    looper.runLoop(nLoops);
    timespec duration = chrono.stop();

    double elapsed = timespec_to_ms(duration) / 1000.0;

    std::cout << "nLoops: " << nLoops << std::endl;
    std::cout << "Execution time: " << std::fixed << std::setprecision(2) << elapsed << " seconds" << std::endl;

    return 0;
}

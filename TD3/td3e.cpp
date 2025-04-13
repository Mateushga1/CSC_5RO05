#include <iostream>
#include <vector>
#include <memory>
#include "Thread_A.h"
#include "Thread_B.h"
#include "Thread_C.h"
#include "Calibrator.h"
#include "Mutex.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <nLoops> <nTasks> [protect] [policy]" << std::endl;
        return 1;
    }

    double nLoops = std::stod(argv[1]);
    int nTasks = std::stoi(argv[2]);
    bool protect = (argc >= 4) ? (std::string(argv[3]) == "true") : false;
    int policy = (argc >= 5) ? (std::string(argv[4]) == "SCHED_RR" ? SCHED_RR :
                (std::string(argv[4]) == "SCHED_FIFO" ? SCHED_FIFO : SCHED_OTHER)) : SCHED_OTHER;

    try {
        Thread::setMainSched(policy);
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    Calibrator calibrator(200.0, 10);
    CpuLoop cpuLoopA(calibrator), cpuLoopB(calibrator), cpuLoopC(calibrator);

    {
        Mutex resource(false);
        Thread_C taskC(0, cpuLoopC, resource);
        Thread_A taskA(1, cpuLoopA, resource);
        Thread_B taskB(2, cpuLoopB);

        Chrono totalTime;
        taskC.start();
        while (totalTime.lap_ms() < 3000) {}
        taskA.start();
        taskB.start();

        taskA.join();
        taskB.join();
        taskC.join();

        std::cout << "Without inheritance: Total time = " << totalTime.lap_ms() << "ms" << std::endl;
    }

    {
        Mutex resource(true);
        Thread_C taskC(0, cpuLoopC, resource);
        Thread_A taskA(1, cpuLoopA, resource);
        Thread_B taskB(2, cpuLoopB);

        Chrono totalTime;
        taskC.start();
        while (totalTime.lap_ms() < 3000) {}
        taskA.start();
        taskB.start();

        taskA.join();
        taskB.join();
        taskC.join();

        std::cout << "With inheritance: Total time = " << totalTime.lap_ms() << "ms" << std::endl;
    }

    return 0;
}

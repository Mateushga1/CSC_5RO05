#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include "Incrementer.h"


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <nLoops> <nTasks> [protect] [policy]" << std::endl;
        return 1;
    }

    double nLoops = std::stod(argv[1]);
    int nTasks = std::stoi(argv[2]);
    bool protect = (argc >= 4) ? (std::string(argv[3]) == "true") : false;
    int policy;

    if (argc >= 5)
    {
        std::string policyStr = argv[4];
        if (policyStr == "SCHED_RR")
        {
            policy = SCHED_RR;
        }
        else if (policyStr == "SCHED_FIFO")
        {
            policy = SCHED_FIFO;
        }
        else
        {
            policy = SCHED_OTHER;
        }
    }
    else
    {
        policy = SCHED_OTHER;
    }

    try
    {
        Thread::setMainSched(policy);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error setting policy: " << e.what() << std::endl;
        return 1;
    }

    Counter counter(protect);
    std::vector<std::unique_ptr<Incrementer>> incrementers;
    Chrono totalChrono;

    for (int i = 0; i < nTasks; ++i)
    {
        incrementers.push_back(std::make_unique<Incrementer>(i, counter, nLoops));
    }

    totalChrono.restart();

    for (auto &task : incrementers)
    {
        task->start();
    }

    for (auto &task : incrementers)
    {
        task->join();
    }

    timespec totalTime = totalChrono.stop();

    double expected = nTasks * nLoops;
    double actual = counter.value();
    double error = ((actual - expected) / expected) * 100.0;

    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Actual: " << actual << std::endl;
    std::cout << "Error: " << error << "%" << std::endl;
    std::cout << "Total Time: " << timespec_to_ms(totalTime) / 1000.0 << "s" << std::endl;

    return 0;
}

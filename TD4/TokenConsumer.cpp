#include "TokenConsumer.h"

TokenConsumer::TokenConsumer(int id, Semaphore &sem)
    : Thread(id), sem(sem) {}

void TokenConsumer::run()
{
    while (true)
    {
        if (!sem.take(500))
        {
            std::cout << "Consumer " << id << ": Timeout occurred." << std::endl;
            break;
        }
        consumed++;
        std::cout << "Consumer " << id << ": Consumed token. Total: " << consumed << std::endl;
    }
}

CountType TokenConsumer::getConsumed() const
{
    return consumed;
}

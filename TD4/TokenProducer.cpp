#include "TokenProducer.h"

TokenProducer::TokenProducer(int id, Semaphore &sem, CountType tokensToProduce)
    : Thread(id), sem(sem), tokensToProduce(tokensToProduce) {}

void TokenProducer::run()
{
    for (CountType i = 0; i < tokensToProduce; ++i)
    {
        sem.give();
        produced++;
        std::cout << "Producer " << id << ": Produced token. Total: " << produced << std::endl;
    }
}

CountType TokenProducer::getProduced() const
{
    return produced;
}

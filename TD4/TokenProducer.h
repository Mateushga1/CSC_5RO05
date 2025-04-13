#ifndef TOKENPRODUCER_H
#define TOKENPRODUCER_H

#include "Semaphore.h"
#include "Thread.h"

class TokenProducer : public Thread
{
public:
    TokenProducer(int id, Semaphore &sem, CountType tokensToProduce);
    void run() override;
    CountType getProduced() const;

private:
    Semaphore &sem;
    CountType tokensToProduce;
    CountType produced = 0;
};
#endif

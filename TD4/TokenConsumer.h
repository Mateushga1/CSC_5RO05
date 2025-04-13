#ifndef TOKENCONSUMER_H
#define TOKENCONSUMER_H

#include "Semaphore.h"
#include "Thread.h"

class TokenConsumer : public Thread
{
public:
    TokenConsumer(int id, Semaphore &sem);
    void run() override;
    CountType getConsumed() const;

private:
    Semaphore &sem;
    CountType consumed = 0;
};
#endif

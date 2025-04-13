#ifndef TOKENCONSUMER_H
#define TOKENCONSUMER_H

#include "Semaphore.h"
#include "Thread.h"

class TokenConsumer : public Thread {
public:
    TokenConsumer(int id, Semaphore& semaphore);
    void run() override;
    Semaphore::CountType getConsumed() const;

private:
    Semaphore& semaphore;
    Semaphore::CountType consumed = 0;
};

#endif

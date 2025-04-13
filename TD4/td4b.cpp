#include <iostream>
#include <vector>
#include <memory>
#include "Semaphore.h"
#include "TokenProducer.h"
#include "TokenConsumer.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <numConsumers> <numProducers> <tokensPerProducer>" << std::endl;
        return 1;
    }

    const int numConsumers = std::stoi(argv[1]);
    const int numProducers = std::stoi(argv[2]);
    const Semaphore::CountType tokensPerProducer = std::stoul(argv[3]);

    Semaphore semaphore;
    std::vector<std::unique_ptr<TokenProducer>> producers;
    std::vector<std::unique_ptr<TokenConsumer>> consumers;

    // Cria produtores
    for (int i = 0; i < numProducers; ++i) {
        producers.emplace_back(std::make_unique<TokenProducer>(i, semaphore, tokensPerProducer));
    }

    // Cria consumidores
    for (int i = 0; i < numConsumers; ++i) {
        consumers.emplace_back(std::make_unique<TokenConsumer>(i, semaphore));
    }

    // Inicia todas as threads
    for (auto& consumer : consumers) {
        consumer->start();
    }
    for (auto& producer : producers) {
        producer->start();
    }

    // Aguarda término
    for (auto& producer : producers) {
        producer->join();
    }
    for (auto& consumer : consumers) {
        consumer->join();
    }

    // Calcula totais
    Semaphore::CountType totalProduced = 0;
    for (auto& producer : producers) {
        totalProduced += producer->getProduced();
    }

    Semaphore::CountType totalConsumed = 0;
    for (auto& consumer : consumers) {
        totalConsumed += consumer->getConsumed();
    }

    std::cout << "Total produzido: " << totalProduced << std::endl;
    std::cout << "Total consumido: " << totalConsumed << std::endl;
    std::cout << "Tokens perdidos: " << (totalProduced - totalConsumed) << std::endl;

    return 0;
}

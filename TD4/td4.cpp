#include <iostream>
#include <vector>
#include <memory>
#include "Semaphore.h"
#include "TokenProducer.h"
#include "TokenConsumer.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <nConsumers> <nProducers> <tokensPerProducer>" << std::endl;
        return 1;
    }

    int nConsumers = std::stoi(argv[1]);
    int nProducers = std::stoi(argv[2]);
    CountType tokensPerProducer = std::stoul(argv[3]);

    Semaphore sem;
    std::vector<std::unique_ptr<TokenProducer>> producers;
    std::vector<std::unique_ptr<TokenConsumer>> consumers;

    // Criar produtores e consumidores
    for (int i = 0; i < nProducers; ++i) {
        producers.push_back(std::make_unique<TokenProducer>(i, sem, tokensPerProducer));
    }

    for (int i = 0; i < nConsumers; ++i) {
        consumers.push_back(std::make_unique<TokenConsumer>(i, sem));
    }

    // Iniciar threads
    for (auto& consumer : consumers) consumer->start();
    for (auto& producer : producers) producer->start();

    // Aguardar conclusão
    for (auto& producer : producers) producer->join();
    for (auto& consumer : consumers) consumer->join();

    // Calcular tokens totais
    CountType totalProduced = 0;
    for (auto& p : producers) totalProduced += p->getProduced();

    CountType totalConsumed = 0;
    for (auto& c : consumers) totalConsumed += c->getConsumed();

    // Resultados
    std::cout << "Total Produced: " << totalProduced << std::endl;
    std::cout << "Total Consumed: " << totalConsumed << std::endl;
    std::cout << "Tokens Lost: " << totalProduced - totalConsumed << std::endl;

    return 0;
}

#include <iostream>
#include "environment.hpp"
#include "agent.hpp"
#include "optimizer.hpp"
#include "ids.hpp"

int main() {
    Environment env;
    Agent agent;
    Optimizer optimizer;
    IDS ids;

    std::string state = env.getState();

    if (ids.detectAnomaly(state)) {
        std::cout << "[IDS] Anomaly detected!" << std::endl;
    }

    std::string action = agent.chooseAction(state);
    std::string optimized = optimizer.optimize(state);

    std::cout << "State: " << state << std::endl;
    std::cout << "Agent Action: " << action << std::endl;
    std::cout << "Optimized Action: " << optimized << std::endl;

    return 0;
}

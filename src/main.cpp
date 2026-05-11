#include <iostream>
#include "environment.hpp"
#include "agent.hpp"
#include "optimizer.hpp"
#include "ids.hpp"
#include "logger.hpp"

int main() {
    Logger::log(Logger::INFO, "SentinelAI Engine Starting...");

    Environment env;
    Agent agent;
    Optimizer opt;
    IDS ids;

    std::string state = env.getState();
    Logger::log(Logger::INFO, "Initial State: " + state);

    std::string action = agent.chooseAction(state);
    Logger::log(Logger::INFO, "Agent Action: " + action);

    std::string optimizedAction = opt.optimize(action);
    Logger::log(Logger::INFO, "Optimized Action: " + optimizedAction);

    double reward = env.getReward(state, optimizedAction);
    std::string nextState = env.nextState(state, optimizedAction);

    Logger::log(Logger::INFO, "Reward: " + std::to_string(reward));
    Logger::log(Logger::INFO, "Next State: " + nextState);

    agent.update(state, optimizedAction, reward, nextState);

    ids.detect(state, optimizedAction);

    Logger::log(Logger::INFO, "SentinelAI Engine Finished.");
    return 0;
}

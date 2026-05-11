#pragma once
#include <string>

class Agent {
public:
    Agent();
    std::string chooseAction(const std::string& state);
    void learn(const std::string& state, const std::string& action, int reward);
};

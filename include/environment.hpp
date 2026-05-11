#pragma once
#include <string>

class Environment {
public:
    std::string getState();
    double getReward(const std::string& state, const std::string& action);
    std::string nextState(const std::string& state, const std::string& action);
};

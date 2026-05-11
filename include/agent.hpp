#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "logger.hpp"

class Agent {
public:
    Agent();

    std::string chooseAction(const std::string& state);
    void update(const std::string& state, const std::string& action,
                double reward, const std::string& nextState);

private:
    std::unordered_map<std::string, std::unordered_map<std::string, double>> Q;
    std::vector<std::string> actions;

    double alpha;
    double gamma;
    double epsilon;

    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;

    void ensureState(const std::string& s);
    std::string randomAction();
    std::string bestAction(const std::string& state);
    double maxQ(const std::string& state);
};

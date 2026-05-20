#pragma once
#include <string>
#include <tuple>

class Environment {
public:
    std::string getState();
    double getReward(const std::string& state, const std::string& action);
    std::string nextState(const std::string& state, const std::string& action);

    std::string reset();
    std::tuple<std::string, double, bool> step(const std::string& action);
    std::string encodeState(int row, int col) const;

private:
    int agentRow;
    int agentCol;
    int startRow;
    int startCol;
};

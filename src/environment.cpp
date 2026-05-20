#include "environment.hpp"
#include <tuple>   // required for std::tuple
#include <string>

std::string Environment::encodeState(int row, int col) const {
    return std::to_string(row) + "," + std::to_string(col);
}

std::string Environment::reset() {
    // Hard‑coded start position for now
    startRow = 0;
    startCol = 0;

    agentRow = startRow;
    agentCol = startCol;

    return encodeState(agentRow, agentCol);
}

std::tuple<std::string, double, bool> Environment::step(const std::string& action) {
    // Grid boundaries (0..4)
    const int maxRow = 4;
    const int maxCol = 4;

    // Move based on action
    if (action == "UP" && agentRow > 0) {
        agentRow--;
    } 
    else if (action == "DOWN" && agentRow < maxRow) {
        agentRow++;
    } 
    else if (action == "LEFT" && agentCol > 0) {
        agentCol--;
    } 
    else if (action == "RIGHT" && agentCol < maxCol) {
        agentCol++;
    }

    // Reward logic
    double reward = 0.0;
    bool done = false;

    // Goal at bottom‑right corner
    if (agentRow == maxRow && agentCol == maxCol) {
        reward = 1.0;
        done = true;
    }

    // Encode next state
    std::string nextState = encodeState(agentRow, agentCol);

    return { nextState, reward, done };
}

std::string Environment::getState() {
    // Return the agent’s current encoded position
    return encodeState(agentRow, agentCol);
}

// These are placeholders for now — not used in the RL loop
double Environment::getReward(const std::string& state, const std::string& action) {
    return 0.0;
}

std::string Environment::nextState(const std::string& state, const std::string& action) {
    return state;
}

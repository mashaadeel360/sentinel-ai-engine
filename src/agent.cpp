#include "agent.hpp"

Agent::Agent() {}

std::string Agent::chooseAction(const std::string& state) {
    return "move_forward";
}

void Agent::learn(const std::string& state, const std::string& action, int reward) {
    // Placeholder for RL learning logic
}

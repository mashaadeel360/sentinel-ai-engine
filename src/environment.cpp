#include "environment.hpp"

std::string Environment::getState() {
    return "default_state";
}

double Environment::getReward(const std::string& state, const std::string& action) {
    if (action == "move_forward") return 1.0;
    return 0.0;
}

std::string Environment::nextState(const std::string& state, const std::string& action) {
    return "default_state"; // placeholder
}

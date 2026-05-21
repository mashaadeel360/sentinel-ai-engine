#include "agent.hpp"

Agent::Agent()
    : actions({"move_forward", "turn_left", "turn_right"}),
      alpha(0.1), gamma(0.9), epsilon(0.2),
      rng(std::random_device{}()), dist(0.0, 1.0) {}

void Agent::ensureState(const std::string& s) {
    if (!Q.count(s)) {
        for (auto& a : actions) Q[s][a] = 0.0;
    }
}

std::string Agent::randomAction() {
    return actions[rng() % actions.size()];
}

std::string Agent::bestAction(const std::string& state) {
    auto& row = Q[state];
    return std::max_element(row.begin(), row.end(),
        [](auto& a, auto& b) { return a.second < b.second; })->first;
}

double Agent::maxQ(const std::string& state) {
    auto& row = Q[state];
    return std::max_element(row.begin(), row.end(),
        [](auto& a, auto& b) { return a.second < b.second; })->second;
}

std::string Agent::chooseAction(const std::string& state) {
    ensureState(state);

    double r = dist(rng);
    if (r < epsilon) {
        Logger::log(Logger::INFO, "Choosing random action (exploration)");
        return randomAction();
    }

    Logger::log(Logger::INFO, "Choosing best action (exploitation)");
    return bestAction(state);
}

void Agent::update(const std::string& state, const std::string& action,
                   double reward, const std::string& nextState) {
    ensureState(state);
    ensureState(nextState);

    double oldQ = Q[state][action];
    double maxNext = maxQ(nextState);

    double newQ = oldQ + alpha * (reward + gamma * maxNext - oldQ);
    Q[state][action] = newQ;

    Logger::log(Logger::INFO,
        "Updated Q-value for (" + state + ", " + action + "): " + std::to_string(newQ));
}

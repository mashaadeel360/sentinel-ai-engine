#include "agent.hpp"
#include "logger.hpp"
#include <algorithm>
#include <iostream>

// Constructor
Agent::Agent()
    : actions({"UP", "DOWN", "LEFT", "RIGHT"}),
      alpha(0.1),
      gamma(0.9),
      bufferSize(10000),
      rng(std::random_device{}()),
      dist(0.0, 1.0)
{
}

// Ensure state exists in Q-table
void Agent::ensureState(const std::string& s) {
    if (!Q.count(s)) {
        for (const auto& a : actions)
            Q[s][a] = 0.0;
    }
}

// Safe Q-value getter
double Agent::getQValue(const std::string& state, const std::string& action) const {
    auto it = Q.find(state);
    if (it == Q.end()) return 0.0;
    auto it2 = it->second.find(action);
    if (it2 == it->second.end()) return 0.0;
    return it2->second;
}

// Epsilon-greedy action selection
std::string Agent::chooseAction(const std::string& state, double epsilon) {
    ensureState(state);

    // Exploration
    if (dist(rng) < epsilon) {
        Logger::log(Logger::INFO, "Choosing random action (exploration)");
        return actions[rng() % actions.size()];
    }

    // Exploitation
    Logger::log(Logger::INFO, "Choosing best action (exploitation)");

    double bestValue = -1e9;
    std::string bestAction = actions[0];

    for (const auto& a : actions) {
        double q = getQValue(state, a);
        if (q > bestValue) {
            bestValue = q;
            bestAction = a;
        }
    }

    return bestAction;
}

// Q-learning update
void Agent::update(const std::string& state,
                   const std::string& action,
                   double reward,
                   const std::string& nextState)
{
    ensureState(state);
    ensureState(nextState);

    double oldQ = Q[state][action];

    // max_a Q(s', a)
    double maxNextQ = -1e9;
    for (const auto& a : actions) {
        maxNextQ = std::max(maxNextQ, getQValue(nextState, a));
    }

    // Q-learning update rule
    double newQ = oldQ + alpha * (reward + gamma * maxNextQ - oldQ);
    Q[state][action] = newQ;

    Logger::log(Logger::INFO,
        "Updated Q-value for (" + state + ", " + action + "): " + std::to_string(newQ));
}

// Print Q-table heatmap
void Agent::printQValues() const {
    std::cout << "\n=== Q‑Value Heatmap ===\n";

    for (const auto& [state, actionsMap] : Q) {
        std::cout << state << " -> ";
        for (const auto& [action, value] : actionsMap) {
            std::cout << action << ": " << value << "  ";
        }
        std::cout << "\n";
    }

    std::cout << "=======================\n";
}

// Store transition in replay buffer
void Agent::storeTransition(const std::string& s,
                            const std::string& a,
                            double r,
                            const std::string& ns,
                            bool done)
{
    if (replayBuffer.size() >= bufferSize)
        replayBuffer.erase(replayBuffer.begin());

    replayBuffer.push_back({s, a, r, ns, done});
}

// Sample a random transition
Agent::Transition Agent::sampleTransition() const {
    int idx = rng() % replayBuffer.size();
    return replayBuffer[idx];
}

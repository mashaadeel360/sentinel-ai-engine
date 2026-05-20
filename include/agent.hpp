#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <random>
#include <tuple>

class Agent {
public:
    Agent();

    // Epsilon-greedy action selection
    std::string chooseAction(const std::string& state, double epsilon);

    // Q-learning update
    void update(const std::string& state,
                const std::string& action,
                double reward,
                const std::string& nextState);

    // Debugging: print Q-table heatmap
    void printQValues() const;

    // Replay buffer (DQN-style)
    struct Transition {
        std::string state;
        std::string action;
        double reward;
        std::string nextState;
        bool done;
    };

    void storeTransition(const std::string& s,
                         const std::string& a,
                         double r,
                         const std::string& ns,
                         bool done);

    Transition sampleTransition() const;

    std::vector<Transition> replayBuffer;   // public so main.cpp can check size

private:
    // Q-table: Q[state][action] = value
    std::unordered_map<std::string, std::unordered_map<std::string, double>> Q;

    // Valid actions for GridWorld
    std::vector<std::string> actions;

    // Learning parameters
    double alpha;   // learning rate
    double gamma;   // discount factor

    // Replay buffer settings
    size_t bufferSize;

    // RNG for epsilon-greedy + replay sampling
    mutable std::mt19937 rng;
    mutable std::uniform_real_distribution<double> dist;

    // Helpers
    void ensureState(const std::string& s);
    double getQValue(const std::string& state, const std::string& action) const;
};

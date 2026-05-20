#include <iostream>
#include "environment.hpp"
#include "agent.hpp"
#include "optimizer.hpp"
#include "ids.hpp"
#include "logger.hpp"

int main() {
    Logger::log(Logger::INFO, "SentinelAI Training Starting...");

    Environment env;
    Agent agent;
    Optimizer opt;
    IDS ids;

    const int EPISODES = 500;
    double epsilon = 1.0;          // start with full exploration
    const double minEpsilon = 0.05;
    const double decayRate = 0.995;

    for (int episode = 1; episode <= EPISODES; episode++) {

        std::string state = env.reset();
        bool done = false;
        double totalReward = 0.0;
        int steps = 0;

        while (!done) {

            // Agent chooses an action using epsilon-greedy
            std::string action = agent.chooseAction(state, epsilon);

            // Optional: optimizer modifies the action
            std::string optimizedAction = opt.optimize(action);

            // Environment processes the action
            auto [nextState, reward, finished] = env.step(optimizedAction);

            // Store transition in replay buffer
            agent.storeTransition(state, optimizedAction, reward, nextState, finished);

            // If enough experience, sample and update
            if (agent.replayBuffer.size() > 100) {
                auto t = agent.sampleTransition();
                agent.update(t.state, t.action, t.reward, t.nextState);
            } else {
                // Early training: update directly
                agent.update(state, optimizedAction, reward, nextState);
            }

            // IDS monitoring
            ids.detect(state, optimizedAction);

            // Move to next state
            state = nextState;
            done = finished;
            totalReward += reward;
            steps++;

            // OPTIONAL: print grid every step (comment out if too spammy)
            // env.printGrid();
        }

        // Log episode summary
        Logger::log(Logger::INFO,
            "Episode " + std::to_string(episode) +
            " | Reward: " + std::to_string(totalReward) +
            " | Steps: " + std::to_string(steps) +
            " | Epsilon: " + std::to_string(epsilon)
        );

        // Print Q-values every 50 episodes
        if (episode % 50 == 0) {
            agent.printQValues();
        }

        // Epsilon decay
        epsilon = std::max(minEpsilon, epsilon * decayRate);
    }

    Logger::log(Logger::INFO, "Training Complete.");
    return 0;
}

#include <iostream>
#include "environment.hpp"
#include "agent.hpp"
#include "optimizer.hpp"
#include "ids.hpp"
#include "logger.hpp"

int main() {
    Logger::log(Logger::INFO, "SentinelAI Engine Starting...");

    Environment env;
    Agent agent;
    Optimizer opt;
    IDS ids;

    int max_episodes = 5; // Train for 5 episodes as a test

    for (int episode = 1; episode <= max_episodes; ++episode) {
        Logger::log(Logger::INFO, "--- Starting Episode " + std::to_string(episode) + " ---");
        
        std::string state = env.reset();
        bool done = false;
        int steps = 0;

        while (!done && steps < 100) { // 100 step limit to prevent infinite wandering
            std::string action = agent.chooseAction(state);
            std::string optimizedAction = opt.optimize(action); // Note: returns "optimized_action" which will break movement until opt is fixed to return valid directions!
            
            // For now, bypass the optimizer stub so the agent can actually move:
            optimizedAction = action; 

            StepResult result = env.step(optimizedAction);

            agent.update(state, optimizedAction, result.reward, result.next_state);
            ids.detect(state, optimizedAction);

            state = result.next_state;
            done = result.done;
            steps++;
        }
        
        Logger::log(Logger::INFO, "Episode finished in " + std::to_string(steps) + " steps.");
    }

    Logger::log(Logger::INFO, "SentinelAI Engine Finished.");
    return 0;
}

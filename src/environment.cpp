#include "environment.hpp"
Environment::Environment() {
    grid_size = 5;
    start_pos = {0, 0};
    goal_pos = {4, 4};
    walls = {{1, 1}, {2, 2}, {3, 3}};
    agent_pos = start_pos;
}
std::string Environment::positionToString(const Position& pos) {
    return std::to_string(pos.x) + "," + std::to_string(pos.y);
}
std::string Environment::reset() {
    agent_pos = start_pos;
    return getState();
}

std::string Environment::getState() {
    return positionToString(agent_pos);
}


StepResult Environment::step(const std::string& action) {
    Position next_pos = agent_pos;

    if(action == "UP") next_pos.y -=1;
    else if (action == "RIGHT") next_pos.x +=1;
    else if (action == "DOWN") next_pos.y += 1;
    else if (action == "LEFT") next_pos.x -= 1;

    //wall collision check
    bool hit_wall = false;
    for (const auto& wall:walls){
        if(next_pos == wall){
        hit_wall = true;
        break;
        }
    }
    //movement
    if(!hit_wall && 
        next_pos.x >= 0 && next_pos.x < grid_size &&
        next_pos.y >= 0 && next_pos.y < grid_size) {
        agent_pos = next_pos;
    }

    bool done = (agent_pos == goal_pos);
    double reward = done ? 1.0 : -0.01;
    return {getState(), reward, done};
}

double Environment::getReward(const std::string& state, const std::string& action) {
    if (action == "move_forward") return 1.0;
    return 0.0;
}

std::string Environment::nextState(const std::string& state, const std::string& action) {
    return "default_state"; // placeholder
}

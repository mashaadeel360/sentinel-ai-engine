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
   else
}

double Environment::getReward(const std::string& state, const std::string& action) {
    if (action == "move_forward") return 1.0;
    return 0.0;
}

std::string Environment::nextState(const std::string& state, const std::string& action) {
    return "default_state"; // placeholder
}

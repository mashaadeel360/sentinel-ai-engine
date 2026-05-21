#pragma once
#include <string>
#include <vector>
struct Position {
    int x,y;
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};
struct StepResult{
    std::string next_state;
    double reward;
    bool done;
};
class Environment {
private:
    int grid_size;
    Position start_pos;
    Position goal_pos;
    std::vector<Position> walls;
    Position agent_pos;

    std::string positionToString(const Position& pos);
public:
    Environment();
    std::string reset();
    std::string getState();
    StepResult step(const std::string& action);
    double getReward(const std::string& state, const std::string& action);
    std::string nextState(const std::string& state, const std::string& action);
};

#pragma once
#include <string>

class Environment {
public:
    Environment();
    std::string getState();
    void update();
};

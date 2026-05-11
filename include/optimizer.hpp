#pragma once
#include <string>

class Optimizer {
public:
    Optimizer();
    std::string optimize(const std::string& state);
};
